# 获取当前目录下的所有源文件项目
file(GLOB SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/*cc)
list(REMOVE_ITEM SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
list(REMOVE_ITEM SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/qps_test.cc)  # 从库文件编译中移除qps_test.cc


# 创建共享库
add_library(src_lib SHARED ${SRC_FILE})

#创建可执行文件
add_executable(main  main.cc)
# 创建qps_test可执行文件
add_executable(qps_test qps_test.cc)

#链接必要的库
target_link_libraries(main src_lib memory_lib log_lib ${LIBS})
target_link_libraries(qps_test src_lib memory_lib log_lib ${LIBS})  # 链接qps_test需要的库

