# Linux 64位系统上使用到的系统调用

### 发布者
```bash
./DDSHelloWorldExample publisher
Starting 
Publisher running 10 samples.
Publisher matched.
Message: HelloWorld with index: 1 SENT
Message: HelloWorld with index: 2 SENT
Message: HelloWorld with index: 3 SENT
Message: HelloWorld with index: 4 SENT
Message: HelloWorld with index: 5 SENT
Message: HelloWorld with index: 6 SENT
Message: HelloWorld with index: 7 SENT
Message: HelloWorld with index: 8 SENT
Message: HelloWorld with index: 9 SENT
Message: HelloWorld with index: 10 SENT
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 68.00    0.008722         396        22           futex
 13.44    0.001724         123        14           sendto
  3.91    0.000502          41        12           munmap
  2.54    0.000326          40         8           clone3
  1.96    0.000251          13        19         8 setsockopt
  1.93    0.000247           3        63           mmap
  1.58    0.000203           5        39           close
  1.43    0.000183           7        23           mprotect
  0.76    0.000097           1        79        55 openat
  0.54    0.000069          69         1           clock_nanosleep
  0.51    0.000066           4        14           socket
  0.38    0.000049           6         8         1 unlink
  0.37    0.000048          16         3         3 shutdown
  0.32    0.000041           2        15           brk
  0.30    0.000038           4         9           epoll_ctl
  0.27    0.000035           2        17           rt_sigprocmask
  0.23    0.000030           0        33        10 newfstatat
  0.20    0.000026           2         9           bind
  0.20    0.000026           2        10           flock
  0.20    0.000026           8         3           fallocate
  0.19    0.000024           6         4           write
  0.13    0.000017           0        18           recvmsg
  0.06    0.000008           0        16           read
  0.06    0.000008           1         6           getsockname
  0.06    0.000008           8         1           link
  0.06    0.000008           8         1           eventfd2
  0.05    0.000006           1         5           ioctl
  0.05    0.000006           3         2           getsockopt
  0.04    0.000005           2         2           getrandom
  0.03    0.000004           1         3           fchmod
  0.03    0.000004           4         1           set_tid_address
  0.03    0.000004           4         1           timerfd_create
  0.03    0.000004           4         1           epoll_create1
  0.02    0.000003           1         2         1 arch_prctl
  0.02    0.000003           3         1           set_robust_list
  0.02    0.000003           3         1           rseq
  0.02    0.000002           0         5           getpid
  0.01    0.000001           0         2           lseek
  0.00    0.000000           0         1           rt_sigaction
  0.00    0.000000           0         4           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         2         2 connect
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           uname
  0.00    0.000000           0         1           geteuid
  0.00    0.000000           0         1           prlimit64
------ ----------- ----------- --------- --------- ----------------
100.00    0.012827          26       485        81 total
```
### 订阅者
```bash
/DDSHelloWorldExample subscriber
Starting 
Subscriber running. Please press enter to stop the Subscriber
Subscriber matched.
Message HelloWorld 1 RECEIVED
Message HelloWorld 2 RECEIVED
Message HelloWorld 3 RECEIVED
Message HelloWorld 4 RECEIVED
Message HelloWorld 5 RECEIVED
Message HelloWorld 6 RECEIVED
Message HelloWorld 7 RECEIVED
Message HelloWorld 8 RECEIVED
Message HelloWorld 9 RECEIVED
Message HelloWorld 10 RECEIVED
Subscriber unmatched.
^Cstrace: Process 157950 detached
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 17.85    0.002071          26        79        55 openat
 10.09    0.001171          18        62           mmap
  7.91    0.000918          65        14         3 setsockopt
  6.89    0.000800          28        28           futex
  6.46    0.000750          22        34        10 newfstatat
  6.32    0.000733          81         9           sendto
  5.66    0.000657          43        15           rt_sigprocmask
  4.33    0.000502          22        22           mprotect
  4.05    0.000470          16        28           close
  3.83    0.000445          24        18           recvmsg
  3.58    0.000415          59         7           clone3
  3.12    0.000362          25        14           socket
  2.22    0.000258          16        16           read
  2.12    0.000246          15        16           brk
  2.05    0.000238          79         3           fallocate
  1.67    0.000194          21         9           epoll_ctl
  1.39    0.000161          17         9           bind
  1.22    0.000142          17         8           flock
  1.12    0.000130          26         5         1 unlink
  1.10    0.000128          32         4           write
  0.90    0.000105          17         6           getsockname
  0.83    0.000096          32         3           fchmod
  0.73    0.000085          21         4           pread64
  0.67    0.000078          15         5           ioctl
  0.65    0.000076          15         5           getpid
  0.50    0.000058          19         3           munmap
  0.33    0.000038          19         2           getsockopt
  0.32    0.000037          18         2         2 connect
  0.29    0.000034          34         1         1 access
  0.28    0.000033          16         2           lseek
  0.26    0.000030          15         2         1 arch_prctl
  0.22    0.000026          26         1           link
  0.20    0.000023          23         1           timerfd_create
  0.18    0.000021          21         1           eventfd2
  0.17    0.000020          20         1           epoll_create1
  0.16    0.000018          18         1           rt_sigaction
  0.14    0.000016           8         2           getrandom
  0.09    0.000010          10         1           uname
  0.09    0.000010          10         1           geteuid
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00    0.011605          25       449        73 total
```

## `64位Linux`系统调用整理

**返回值放在`%rax`中**

| %rax  | syscall           | Entry point                                                                                                                                   | Manual                                                                                            |
| ----- | ----------------- | --------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| `202` | `futex`           | [sys_futex](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbfutex%5Cb%2F&type=code)                     | [futex(2)](https://manpages.debian.org/unstable/manpages-dev/futex.2.en.html)                     |
| `44`  | `sendto`          | [sys_sendto](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbsendto%5Cb%2F&type=code)                   | [sendto(2)](https://manpages.debian.org/unstable/manpages-dev/sendto.2.en.html)                   |
| `11`  | `munmap`          | [sys_munmap](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbmunmap%5Cb%2F&type=code)                   | [munmap(2)](https://manpages.debian.org/unstable/manpages-dev/munmap.2.en.html)                   |
| `435` | `clone3`          | [sys_clone3](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbclone3%5Cb%2F&type=code)                   | [clone3(2)](https://manpages.debian.org/unstable/manpages-dev/clone3.2.en.html)                   |
| `54`  | `setsockopt`      | [sys_setsockopt](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbsetsockopt%5Cb%2F&type=code)           | [setsockopt(2)](https://manpages.debian.org/unstable/manpages-dev/setsockopt.2.en.html)           |
| `9`   | `mmap`            | [sys_mmap](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbmmap%5Cb%2F&type=code)                       | [mmap(2)](https://manpages.debian.org/unstable/manpages-dev/mmap.2.en.html)                       |
| `3`   | `close`           | [sys_close](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbclose%5Cb%2F&type=code)                     | [close(2)](https://manpages.debian.org/unstable/manpages-dev/close.2.en.html)                     |
| `10`  | `mprotect`        | [sys_mprotect](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbmprotect%5Cb%2F&type=code)               | [mprotect(2)](https://manpages.debian.org/unstable/manpages-dev/mprotect.2.en.html)               |
| `257` | `openat`          | [sys_openat](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbopenat%5Cb%2F&type=code)                   | [openat(2)](https://manpages.debian.org/unstable/manpages-dev/openat.2.en.html)                   |
| `230` | `clock_nanosleep` | [sys_clock_nanosleep](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbclock_nanosleep%5Cb%2F&type=code) | [clock_nanosleep(2)](https://manpages.debian.org/unstable/manpages-dev/clock_nanosleep.2.en.html) |
| `41`  | `socket`          | [sys_socket](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbsocket%5Cb%2F&type=code)                   | [socket(2)](https://manpages.debian.org/unstable/manpages-dev/socket.2.en.html)                   |
| `87`  | `unlink`          | [sys_unlink](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbunlink%5Cb%2F&type=code)                   | [unlink(2)](https://manpages.debian.org/unstable/manpages-dev/unlink.2.en.html)                   |
| `48`  | `shutdown`        | [sys_shutdown](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbshutdown%5Cb%2F&type=code)               | [shutdown(2)](https://manpages.debian.org/unstable/manpages-dev/shutdown.2.en.html)               |
| `12`  | `brk`             | [sys_brk](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbbrk%5Cb%2F&type=code)                         | [brk(2)](https://manpages.debian.org/unstable/manpages-dev/brk.2.en.html)                         |
| `233` | `epoll_ctl`       | [sys_epoll_ctl](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbepoll_ctl%5Cb%2F&type=code)             | [epoll_ctl(2)](https://manpages.debian.org/unstable/manpages-dev/epoll_ctl.2.en.html)             |
| `14`  | `rt_sigprocmask`  | [sys_rt_sigprocmask](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbrt_sigprocmask%5Cb%2F&type=code)   | [rt_sigprocmask(2)](https://manpages.debian.org/unstable/manpages-dev/rt_sigprocmask.2.en.html)   |
| `262` | `newfstatat`      | [sys_newfstatat](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbnewfstatat%5Cb%2F&type=code)           | [newfstatat(2)](https://manpages.debian.org/unstable/manpages-dev/newfstatat.2.en.html)           |
| `49`  | `bind`            | [sys_bind](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbbind%5Cb%2F&type=code)                       | [bind(2)](https://manpages.debian.org/unstable/manpages-dev/bind.2.en.html)                       |
| `73`  | `flock`           | [sys_flock](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbflock%5Cb%2F&type=code)                     | [flock(2)](https://manpages.debian.org/unstable/manpages-dev/flock.2.en.html)                     |
| `285` | `fallocate`       | [sys_fallocate](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbfallocate%5Cb%2F&type=code)             | [fallocate(2)](https://manpages.debian.org/unstable/manpages-dev/fallocate.2.en.html)             |
| `1`   | `write`           | [sys_write](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbwrite%5Cb%2F&type=code)                     | [write(2)](https://manpages.debian.org/unstable/manpages-dev/write.2.en.html)                     |
| `47`  | `recvmsg`         | [sys_recvmsg](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbrecvmsg%5Cb%2F&type=code)                 | [recvmsg(2)](https://manpages.debian.org/unstable/manpages-dev/recvmsg.2.en.html)                 |
| `0`   | `read`            | [sys_read](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbread%5Cb%2F&type=code)                       | [read(2)](https://manpages.debian.org/unstable/manpages-dev/read.2.en.html)                       |
| `51`  | `getsockname`     | [sys_getsockname](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbgetsockname%5Cb%2F&type=code)         | [getsockname(2)](https://manpages.debian.org/unstable/manpages-dev/getsockname.2.en.html)         |
| `86`  | `link`            | [sys_link](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cblink%5Cb%2F&type=code)                       | [link(2)](https://manpages.debian.org/unstable/manpages-dev/link.2.en.html)                       |
| `290` | `eventfd2`        | [sys_eventfd2](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbeventfd2%5Cb%2F&type=code)               | [eventfd2(2)](https://manpages.debian.org/unstable/manpages-dev/eventfd2.2.en.html)               |
| `16`  | `ioctl`           | [sys_ioctl](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbioctl%5Cb%2F&type=code)                     | [ioctl(2)](https://manpages.debian.org/unstable/manpages-dev/ioctl.2.en.html)                     |
| `55`  | `getsockopt`      | [sys_getsockopt](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbgetsockopt%5Cb%2F&type=code)           | [getsockopt(2)](https://manpages.debian.org/unstable/manpages-dev/getsockopt.2.en.html)           |
| `318` | `getrandom`       | [sys_getrandom](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbgetrandom%5Cb%2F&type=code)             | [getrandom(2)](https://manpages.debian.org/unstable/manpages-dev/getrandom.2.en.html)             |
| `91`  | `fchmod`          | [sys_fchmod](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbfchmod%5Cb%2F&type=code)                   | [fchmod(2)](https://manpages.debian.org/unstable/manpages-dev/fchmod.2.en.html)                   |
| `218` | `set_tid_address` | [sys_set_tid_address](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbset_tid_address%5Cb%2F&type=code) | [set_tid_address(2)](https://manpages.debian.org/unstable/manpages-dev/set_tid_address.2.en.html) |
| `283` | `timerfd_create`  | [sys_timerfd_create](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbtimerfd_create%5Cb%2F&type=code)   | [timerfd_create(2)](https://manpages.debian.org/unstable/manpages-dev/timerfd_create.2.en.html)   |
| `291` | `epoll_create1`   | [sys_epoll_create1](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbepoll_create1%5Cb%2F&type=code)     | [epoll_create1(2)](https://manpages.debian.org/unstable/manpages-dev/epoll_create1.2.en.html)     |
| `158` | `arch_prctl`      | [sys_arch_prctl](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbarch_prctl%5Cb%2F&type=code)           | [arch_prctl(2)](https://manpages.debian.org/unstable/manpages-dev/arch_prctl.2.en.html)           |
| `273` | `set_robust_list` | [sys_set_robust_list](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbset_robust_list%5Cb%2F&type=code) | [set_robust_list(2)](https://manpages.debian.org/unstable/manpages-dev/set_robust_list.2.en.html) |
| `334` | `rseq`            | [sys_rseq](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbrseq%5Cb%2F&type=code)                       | [rseq(2)](https://manpages.debian.org/unstable/manpages-dev/rseq.2.en.html)                       |
| `39`  | `getpid`          | [sys_getpid](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbgetpid%5Cb%2F&type=code)                   | [getpid(2)](https://manpages.debian.org/unstable/manpages-dev/getpid.2.en.html)                   |
| `8`   | `lseek`           | [sys_lseek](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cblseek%5Cb%2F&type=code)                     | [lseek(2)](https://manpages.debian.org/unstable/manpages-dev/lseek.2.en.html)                     |
| `13`  | `rt_sigaction`    | [sys_rt_sigaction](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbrt_sigaction%5Cb%2F&type=code)       | [rt_sigaction(2)](https://manpages.debian.org/unstable/manpages-dev/rt_sigaction.2.en.html)       |
| `17`  | `pread64`         | [sys_pread64](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbpread64%5Cb%2F&type=code)                 | [pread64(2)](https://manpages.debian.org/unstable/manpages-dev/pread64.2.en.html)                 |
| `21`  | `access`          | [sys_access](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbaccess%5Cb%2F&type=code)                   | [access(2)](https://manpages.debian.org/unstable/manpages-dev/access.2.en.html)                   |
| `42`  | `connect`         | [sys_connect](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbconnect%5Cb%2F&type=code)                 | [connect(2)](https://manpages.debian.org/unstable/manpages-dev/connect.2.en.html)                 |
| `59`  | `execve`          | [sys_execve](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbexecve%5Cb%2F&type=code)                   | [execve(2)](https://manpages.debian.org/unstable/manpages-dev/execve.2.en.html)                   |
| `63`  | `uname`           | [sys_uname](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbuname%5Cb%2F&type=code)                     | [uname(2)](https://manpages.debian.org/unstable/manpages-dev/uname.2.en.html)                     |
| `107` | `geteuid`         | [sys_geteuid](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbgeteuid%5Cb%2F&type=code)                 | [geteuid(2)](https://manpages.debian.org/unstable/manpages-dev/geteuid.2.en.html)                 |
| `302` | `prlimit64`       | [sys_prlimit64](https://github.com/search?q=repo%3Atorvalds%2Flinux+%2FSYSCALL_DEFINE%5B%5E%2C%5D*%5Cbprlimit64%5Cb%2F&type=code)             | [prlimit64(2)](https://manpages.debian.org/unstable/manpages-dev/prlimit64.2.en.html)             |
