# Fast-DDS 相关文档

[Fast-DDS 官方文档](https://fast-dds.docs.eprosima.com/en/latest/)

## Fast-DDS 介绍

Fast-DDS 是一个快速的、模块化的、可扩展的、高性能的数据分发系统。它是一个基于数据中心的发布/订阅通信模型的实现，它是为了满足实时系统的需求而设计的。

## Fast-DDS 测例

本repo中包含了Fast-DDS的测试用例, `DDSHelloWorldExample` 和 `LatencyTest`.
```shell
# DDSHelloWorldExample 的运行命令
./DDSHelloWorldExample publisher & ./DDSHelloWorldExample subscriber
# 预期结果如下
Starting 
Starting 
Publisher running 10 samples.
Subscriber running. Please press enter to stop the Subscriber
Subscriber matched.
Publisher matched.
Message: HelloWorld with index: 1 SENT
Message HelloWorld 1 RECEIVED
Message: HelloWorld with index: 2 SENT
Message HelloWorld 2 RECEIVED
Message: HelloWorld with index: 3 SENT
Message HelloWorld 3 RECEIVED
Message: HelloWorld with index: 4 SENT
Message HelloWorld 4 RECEIVED
Message: HelloWorld with index: 5 SENT
Message HelloWorld 5 RECEIVED
Message: HelloWorld with index: 6 SENT
Message HelloWorld 6 RECEIVED
Message: HelloWorld with index: 7 SENT
Message HelloWorld 7 RECEIVED
Message: HelloWorld with index: 8 SENT
Message HelloWorld 8 RECEIVED
Message: HelloWorld with index: 9 SENT
Message HelloWorld 9 RECEIVED
Message: HelloWorld with index: 10 SENT
Message HelloWorld 10 RECEIVED
Subscriber unmatched.
```

```shell
# LatencyTest 的运行命令
./LatencyTest both
# 预期结果如下
Performing intraprocess test with 1 subscribers and 10000 samples
Overhead 0.0222268 us
Printing round-trip times in us, statistics for 10000 samples
   Bytes, Samples,   stdev,    mean,     min,     50%,     90%,     99%,  99.99%,     max
--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,
      16,   10000,   0.658,   1.344,   1.298,   1.333,   1.352,   1.384,   3.829,  66.925 
    1024,   10000,   0.100,   1.831,   1.764,   1.827,   1.852,   1.878,   5.759,   8.327 
   64512,   10000,   1.827,   6.057,   4.473,   5.062,   8.783,   8.851,  16.630,  47.963 
 1048576,   10000,  14.784, 115.073, 112.335, 112.867, 114.099, 181.642, 474.683, 754.915 
EVERYTHING STOPPED FINE
```

## Fast-DDS 编译安装 (可选)
参考`Fast-DDS_install.md`

## starry 下运行 DDSHelloWorldExample

```shell
# 下载最新的starry代码
git clone https://github.com/Arceos-monolithic/Starry.git
cd Starry
# 将 DDSHelloWorldExample 和 LatencyTest 拷贝到 Starry/testcases/sdcard 目录下
./build_img.sh riscv64
make A=apps/monolithic_userboot ARCH=riscv64 run LOG=error

# 进入starry的shell
./DDSHelloWorldExample publisher & ./DDSHelloWorldExample subscriber
# 我们可以看到如下的错误信息
Starting 
[ 20.576142 0:6 axstarry::syscall_net::imp:26] [socket()] Address Family not supported: 16
getifaddrs: Address family not supported by protocol
# 以及
[ 21.756350 0:6 axruntime::lang_items:5] panicked at ulib/axstarry/src/syscall.rs:49:9:
unknown syscall id: 19
```

- 发现`Address family not supported by protocol`, 说明starry目前暂不支持这个id为16的socket类型, 通过在linux源码中查找可以知道, id为16的socket类型是`AF_NETLINK` 
- 发现`unknown syscall id: 19`, 说明starry目前暂不支持这个id为19的系统调用, [查找网站(感谢)](https://jborza.com/post/2021-05-11-riscv-linux-syscalls/), id为19的系统调用是`eventfd2`

## strace对拍

```shell
# 可以使用 strace 获取系统调用的信息, 通过对比linux和starry的系统调用, 辅助发现问题

# 查看 linux 的系统调用
strace -o linux.log ./DDSHelloWorldExample_x86 subscriber

# 查看 starry 的系统调用 直接使用 starry 的 LOG 就行

# 同时提供了riscv64的 Linux 版本 以及 strace, 方便大家使用
./build_img.sh
# 在进入Linux的shell后先
export LD_LIBRARY_PATH=/lib:$LD_LIBRARY_PATH
# 然后即可使用 strace 对拍
# 相关测试文件在 /bin 目录下
# 同时也在根目录下提供了一个简单的 ./test 测试文件 等价于 ./DDSHelloWorldExample publisher & ./DDSHelloWorldExample subscriber

```

## 项目实习任务

使用最新的[starry代码](https://github.com/Arceos-monolithic/Starry.git), 成功运行Fast-DDS的测试用例`LatencyTest`

## 系统调用分析

[Linux64系统调用分析](./Linux64-syscall.md)

[ArceOS系统调用分析](./ArceOS-syscall.md)

## 相关测例程序

[udp multicast](./multicast_test.c)