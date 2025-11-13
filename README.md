# C++项目推荐：kama-webserver | 代码随想录

**本项目目前只在[知识星球](https://programmercarl.com/other/kstar.html)里维护，并答疑**

最近[知识星球](https://programmercarl.com/other/kstar.html)里的项目开启翻新计划，为了应变每年校招求职的变化，很多星球老项目都重构代码并重写项目文档了。

这期给大家重构的项目是 23年在[知识星球](https://programmercarl.com/other/kstar.html)里发布的webserver项目。

## 老生常淡，webserver还能做吗？

关于C++的项目，大家都会知道 webserver。

有一个段子：C++选手人均webserver。

我得给webserver“伸冤”一下，其实**webserver是一个非常好的学习项目，只是这个项目的形式“烂大街”了**，它所涉及的知识依然是经典的。

webserver 所涉及到的知识：

* C++八股（C/C++语法全覆盖、内存管理等、可以扩展至C++11/17）
* 操作系统（线程、进程、锁、还有大量的 I/O 系统调用及其封装还有 EPOLL 等多路复用机制）
* 网络（网络编程，通信，网络异常的处理）
* 数据库（注册中心的数据库语句、负载均衡等）
* 还有设计模式、缓存设计，日志系统，定时器模块等等

**大家背的八股，无非就是 网络，操作系统和数据库，还有C++八股，webserver基本都包含了**，**webserver是八股结合实战非常好的案例**！

可以理解成：**webserver 就是大家背的八股的实战篇**。

webserver 也可以称之为高性能服务器，因为他算是服务器开发，不少录友在简历上不写webserver这个名字，而写的是高性能服务器。

换一个名字好像高级了一些。。。

如果你时间充裕，想系统学习C++，做webserver是非常好的选择，你会发现自己背的八股都活学活用了。

当然，简历上一个webserver 是不够的，还需要再做一个项目。 [知识星球](https://programmercarl.com/other/kstar.html)里有众多项目可以选：

如果你时间紧张，那就别做webserver了，本来形式就是“烂大街”的。

webserver是用来打基础的，也没时间打基础，就把相关八股背一背，突击做一些新颖一些的项目。[知识星球](https://programmercarl.com/other/kstar.html)里目前有10个C++的项目可以选择。

## 高性能服务器项目第二版


文档方面，相对与[第一版](https://mp.weixin.qq.com/s/40ISnd7PkBtAlWv5MQf1vQ) 做了如下优化：

1、开篇：讲述了为什么要学习webserver，以及学习webserver需要什么基础知识。

2、大纲：讲述了整个文章的框架结构。

3、框架梳理：讲述了webserver整体的架构如网络模块、定时器模块、内存池、LFU、日志系统等。

4、代码模块：讲述了上面提到模块以及内存池、LFU的核心代码部分。

5、面试问题：整理了星球录友亲身经历的问题

6、补充简历写法。

## 高性能服务器专栏

该项目的专栏是[知识星球](https://programmercarl.com/other/kstar.html)录友专享的。

项目专栏依然是将 「简历写法」给大家列出来了，大家学完就可以参考这个来写简历：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307105143.png' width=500 alt=''></img></div>

做完该项目，面试中大概率会有哪些面试问题，以及如何回答，也列出好了：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307105324.png' width=500 alt=''></img></div>

专栏中的项目面试题都掌握的话，这个项目在面试中基本没问题。

很多录友在做项目的时候，把项目运行起来 就是第一大难点！

本项目运行起来 需要依赖的环境很多，所以我给大家准备的 自动化环境配置脚本， **项目运行环境，一键配置！ 不需要大家去处理环境问题了**：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307105632.png' width=500 alt=''></img></div>


框架梳理：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307105726.png' width=500 alt=''></img></div>

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307105931.png' width=500 alt=''></img></div>

底层网络模块架构：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307105758.png' width=500 alt=''></img></div>

代码讲解：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307110003.png' width=500 alt=''></img></div>

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307110035.png' width=500 alt=''></img></div>

日志系统的设计：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307110057.png' width=500 alt=''></img></div>

缓冲区的设计：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307110130.png' width=500 alt=''></img></div>

内存管理设计：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307110205.png' width=500 alt=''></img></div>

线程池：

<div align="center"><img src='https://file1.kamacoder.com/i/algo/20250307110234.png' width=500 alt=''></img></div>

## 答疑

本项目在[知识星球](https://programmercarl.com/other/kstar.html)里为 文字专栏形式，大家不用担心，看不懂，星球里每个项目有专属答疑群，任何问题都可以在群里问，都会得到解答：

![](https://file1.kamacoder.com/i/web/2025-09-26_11-30-13.jpg)



## 下载方式

**本文档仅为星球内部专享，大家可以加入[知识星球](https://programmercarl.com/other/kstar.html)里获取，在星球置顶一**

