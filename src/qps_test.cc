#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <errno.h>
#include <mutex>
#include <algorithm>
#include <iomanip>

// 服务器地址和端口
const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 8080;

// 测试参数
const int TEST_DURATION_SECONDS = 30;  // 测试持续时间(秒)
const std::vector<int> CONCURRENT_LEVELS = {5, 10, 20, 50};  // 多级别并发测试
const std::vector<int> REQUEST_SIZES = {100, 1024, 10240};  // 不同请求大小

// 原子计数器用于统计总请求数和成功请求数
std::atomic<int> total_requests(0);
std::atomic<int> successful_requests(0);
std::atomic<long long> total_response_time(0);

// 响应时间统计
std::vector<double> response_times;
std::mutex response_mutex;

// 测试函数支持不同请求大小
void testThread(int request_size) {
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(TEST_DURATION_SECONDS);

    // 创建固定大小的请求消息
    std::string test_message(request_size, 'a');

    while (std::chrono::steady_clock::now() < end_time) {
        // 创建socket
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            continue;
        }

        // 设置服务器地址
        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

        // 连接服务器
        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            close(sockfd);
            continue;
        }

        // 记录发送时间
        auto send_time = std::chrono::steady_clock::now();

        // 发送数据
        send(sockfd, test_message.c_str(), test_message.size(), 0);

        // 接收响应
        char buffer[1024 * 10] = {0};  // 增大缓冲区以适应不同大小的响应
        int recv_len = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

        // 记录接收时间
        auto recv_time = std::chrono::steady_clock::now();
        auto response_time = std::chrono::duration_cast<std::chrono::microseconds>(recv_time - send_time).count();

        // 线程安全地记录响应时间
        {
            std::lock_guard<std::mutex> lock(response_mutex);
            response_times.push_back(response_time);
        }
        total_response_time += response_time;

        // 验证响应
        if (recv_len > 0) {
            std::string response(buffer, recv_len);
            // 更严格的验证：检查内容是否全为'a'
            bool content_match = true;
            for (char c : response) {
                if (c != 'a') {
                    content_match = false;
                    break;
                }
            }
            if (response.size() == test_message.size() && content_match) {
                successful_requests++;
            }
        }

        total_requests++;
        close(sockfd);
    }
}

// 修改runConcurrencyTest函数，专注于单一测试场景
void runConcurrencyTest(int concurrency, int request_size) {
    // 重置计数器
    total_requests = 0;
    successful_requests = 0;
    total_response_time = 0;
    response_times.clear();

    std::cout << "Testing with " << concurrency << " threads and "
              << request_size << " bytes requests..." << std::endl;

    // 创建线程池
    std::vector<std::thread> threads;
    auto start_time = std::chrono::steady_clock::now();

    for (int i = 0; i < concurrency; ++i) {
        threads.emplace_back(testThread, request_size);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    // 计算QPS
    double qps = total_requests / static_cast<double>(duration);

    // 输出结果
    std::cout << "Test completed!" << std::endl;
    std::cout << "Total requests: " << total_requests << std::endl;
    std::cout << "Successful requests: " << successful_requests << std::endl;
    std::cout << "Success rate: " << (successful_requests * 100.0 / total_requests) << "%" << std::endl;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
    std::cout << "QPS: " << std::fixed << std::setprecision(2) << qps << std::endl;

    // 输出响应时间统计
    if (!response_times.empty()) {
        std::sort(response_times.begin(), response_times.end());
        double avg_time = total_response_time / static_cast<double>(response_times.size());
        double p50 = response_times[response_times.size() / 2];
        double p90 = response_times[response_times.size() * 9 / 10];
        double p99 = response_times[response_times.size() * 99 / 100];
        double min_time = response_times.front();
        double max_time = response_times.back();

        std::cout << "Response time statistics (microseconds):" << std::endl;
        std::cout << "  Min: " << min_time << std::endl;
        std::cout << "  Average: " << std::fixed << std::setprecision(2) << avg_time << std::endl;
        std::cout << "  P50: " << p50 << std::endl;
        std::cout << "  P90: " << p90 << std::endl;
        std::cout << "  P99: " << p99 << std::endl;
        std::cout << "  Max: " << max_time << std::endl;
    }
}

// 添加完整的main函数
int main() {
    std::cout << "Starting QPS test for Kama WebServer..." << std::endl;
    std::cout << "Server: " << SERVER_IP << ":" << SERVER_PORT << std::endl;
    std::cout << "Test duration: " << TEST_DURATION_SECONDS << " seconds" << std::endl;

    // 1. 可选：添加预热阶段
    std::cout << "Warming up server..." << std::endl;
    runConcurrencyTest(5, 100);  // 低并发预热
    std::cout << "Warm-up complete. Starting formal test..." << std::endl;

    // 2. 测试不同并发级别（固定请求大小）
    std::cout << "\n=== Testing different concurrency levels (100B requests) ===" << std::endl;
    for (int concurrency : CONCURRENT_LEVELS) {
        runConcurrencyTest(concurrency, 100);
        std::cout << "------------------------------" << std::endl;
    }

    // 3. 测试不同请求大小（固定并发级别）
    std::cout << "\n=== Testing different request sizes (10 threads) ===" << std::endl;
    for (int size : REQUEST_SIZES) {
        runConcurrencyTest(10, size);
        std::cout << "------------------------------" << std::endl;
    }

    return 0;
}