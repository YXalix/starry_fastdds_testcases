## Fast-DDS任务

`socket(AF_NETLINK, SOCK_RAW|SOCK_CLOEXEC, NETLINK_ROUTE) = 3` 实现 `NETLINK_ROUTE`, 分别需要实现处理`RTM_GETLINK` 和 `RTM_GETADDR`请求, 参考源码中的`static int get_route_table(int rtm_family)`是怎么获取route_table的, 如果对`Linux`源码不太熟悉可参考[rust-netlink/netlink-packet-route](https://github.com/rust-netlink/netlink-packet-route)来快速理解`message`的组织方式

- 写对应的测试用例, 测试自己返回的`message`是否符合要求
- 缺失`bind, sendto, recvfrom`这三个系统调用

`socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) = 8`, 实现多播, 首先增加`smoltcp`的`feature=proto-igmp` 来获取`igmp`支持, 后续相关实现多阅读`smoltcp`源码

- 编写对应的测试用例, 测试是否能实现本地多播
- 缺失`bind(5, {sa_family=AF_INET, sin_port=htons(7400), sin_addr=inet_addr("0.0.0.0")}, 16) = 0`
- 缺失`setsockopt(8, SOL_IP, IP_MULTICAST_TTL, "\1", 1) = 0`
- 缺失`setsockopt(8, SOL_IP, IP_MULTICAST_LOOP, [1], 4) = 0`
- 缺失`setsockopt(8, SOL_IP, IP_MULTICAST_IF, [16777343], 4) = 0`
- 缺失`setsockopt(5, SOL_IP, IP_ADD_MEMBERSHIP,{imr_multiaddr=inet_addr("239.255.0.1"), imr_interface=inet_addr("127.0.0.1")}, 8) = 0`

`eventfd2(0, EFD_CLOEXEC|EFD_NONBLOCK) = 3`
- 编写测试用例, 测试基本的`read`和`write`能否实现
- 先实现基本的`read` 和 `write`
- 实现完善版本的`eventfd`
