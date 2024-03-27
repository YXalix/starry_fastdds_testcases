# ArceOS系统调用 - FastDDS在ArceOS中的系统调用

## 发布者

```shell
/bin/DDSHelloWorldExample publisher
Starting 
terminate called after throwing an instance of 'std::runtime_error'
  what():  random_device::random_device(const std::string&)
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ------------------
 31.70    0.004095         102        40           mmap
 16.70    0.002157         308         7           writev
 13.78    0.001781         222         8           munmap
 12.31    0.001591         198         8           recvfrom
  9.54    0.001233         308         4           sendto
  4.45    0.000575         287         2           close
  2.83    0.000366         366         1           set_tid_address
  2.63    0.000340         113         3         3 openat
  1.91    0.000247         123         2           socket
  1.29    0.000167          83         2           brk
  0.98    0.000127          63         2           rt_sigprocmask
  0.53    0.000069          69         1           tkill
  0.52    0.000067          67         1           ioctl
  0.48    0.000062          62         1           sched_getaffinity
  0.33    0.000043          43         1           getpid
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ------------------
100.00    0.012920         153        84         3 total
Aborted
```

## 订阅者

```shell
/bin/DDSHelloWorldExample subscriber
Starting 
terminate called after throwing an instance of 'std::runtime_error'
  what():  random_device::random_device(const std::string&)
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ------------------
 23.69    0.004032         100        40           mmap
 18.03    0.003069        3069         1           execve
 14.94    0.002543         363         7           writev
 14.09    0.002399         599         4           sendto
 10.78    0.001835         229         8           recvfrom
  8.58    0.001461         182         8           munmap
  1.84    0.000314         314         1           set_tid_address
  1.79    0.000305         152         2           close
  1.54    0.000263          87         3         3 openat
  1.47    0.000251         250         1           tkill
  0.83    0.000141          70         2           brk
  0.72    0.000122          61         2           rt_sigprocmask
  0.70    0.000119          59         2           socket
  0.39    0.000067          67         1           ioctl
  0.33    0.000057          57         1           sched_getaffinity
  0.26    0.000045          45         1           getpid
------ ----------- ----------- --------- --------- ------------------
100.00    0.017023         202        84         3 total
Aborted
```

## `ArceOS` 在 `RISC-V` 架构下的系统调用整理

| #     | syscall                                                                             | prototype                                                                                                                              |
| ----- | ----------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| `222` | [mmap](https://man7.org/linux/man-pages/man2/mmap.2.html)                           | asmlinkage long sys_old_mmap(struct mmap_arg_struct __user *arg);                                                                      |
| `221` | [execve](https://man7.org/linux/man-pages/man2/execve.2.html)                       | asmlinkage long sys_execve(const char __user *filename, const char __user *const __user *argv, const char __user *const __user *envp); |
| `66`  | [writev](https://man7.org/linux/man-pages/man2/writev.2.html)                       | asmlinkage long sys_writev(unsigned long fd, const struct iovec __user *vec, unsigned long vlen);                                      |
| `206` | [sendto](https://man7.org/linux/man-pages/man2/sendto.2.html)                       | asmlinkage long sys_sendto(int, void __user *, size_t, unsigned, struct sockaddr __user *, int);                                       |
| `207` | [recvfrom](https://man7.org/linux/man-pages/man2/recvfrom.2.html)                   | asmlinkage long sys_recvfrom(int, void __user *, size_t, unsigned, struct sockaddr __user *, int __user *);                            |
| `215` | [munmap](https://man7.org/linux/man-pages/man2/munmap.2.html)                       | asmlinkage long sys_munmap(unsigned long addr, size_t len);                                                                            |
| `96`  | [set_tid_address](https://man7.org/linux/man-pages/man2/set_tid_address.2.html)     | asmlinkage long sys_set_tid_address(int __user *tidptr);                                                                               |
| `57`  | [close](https://man7.org/linux/man-pages/man2/close.2.html)                         | asmlinkage long sys_close(unsigned int fd);                                                                                            |
| `56`  | [openat](https://man7.org/linux/man-pages/man2/openat.2.html)                       | asmlinkage long sys_openat(int dfd, const char __user *filename, int flags, umode_t mode);                                             |
| `130` | [tkill](https://man7.org/linux/man-pages/man2/tkill.2.html)                         | asmlinkage long sys_tkill(pid_t pid, int sig);                                                                                         |
| `214` | [brk](https://man7.org/linux/man-pages/man2/brk.2.html)                             | asmlinkage long sys_brk(unsigned long brk);                                                                                            |
| `135` | [rt_sigprocmask](https://man7.org/linux/man-pages/man2/rt_sigprocmask.2.html)       | asmlinkage long sys_rt_sigprocmask(int how, sigset_t __user *set, sigset_t __user *oset, size_t sigsetsize);                           |
| `198` | [socket](https://man7.org/linux/man-pages/man2/socket.2.html)                       | asmlinkage long sys_socket(int, int, int);                                                                                             |
| `29`  | [ioctl](https://man7.org/linux/man-pages/man2/ioctl.2.html)                         | asmlinkage long sys_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg);                                                       |
| `123` | [sched_getaffinity](https://man7.org/linux/man-pages/man2/sched_getaffinity.2.html) | asmlinkage long sys_sched_getaffinity(pid_t pid, unsigned int len, unsigned long __user *user_mask_ptr);                               |
| `172` | [getpid](https://man7.org/linux/man-pages/man2/getpid.2.html)                       | asmlinkage long sys_getpid(void);                                                                                                      |

### 下面是`LatencyTest`新增的系统调用

| #     | syscall                                                                     | prototype                                                                                                                            |
| ----- | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| `220` | [clone](https://man7.org/linux/man-pages/man2/clone.2.html)                 | asmlinkage long sys_clone(unsigned long, unsigned long, int __user *, unsigned long, int __user *);                                  |
| `422` | [futex](https://man7.org/linux/man-pages/man2/futex.2.html)                 | asmlinkage long sys_futex(u32 __user *uaddr, int op, u32 val, struct __kernel_timespec __user *utime, u32 __user *uaddr2, u32 val3); |
| `226` | [mprotect](https://man7.org/linux/man-pages/man2/mprotect.2.html)           | asmlinkage long sys_mprotect(unsigned long start, size_t len, unsigned long prot);                                                   |
| `430` | [clock_gettime](https://man7.org/linux/man-pages/man2/clock_gettime.2.html) | asmlinkage long sys_clock_gettime(clockid_t which_clock, struct __kernel_timespec __user *tp);                                       |

## `LatencyTest` 在 `RISC-V` 架构下的系统调用整理

```shell
/bin/LatencyTest both
Performing intraprocess test with 1 subscribers and 10000 samples
terminate called after throwing an instance of 'std::runtime_error'
  what():  random_device::random_device(const std::string&)
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ------------------
 17.81    0.002460          51        48           mmap
 17.44    0.002409         344         7           writev
 16.88    0.002331        2331         1           execve
 10.79    0.001491         135        11           munmap
  9.25    0.001278         159         8           recvfrom
  5.97    0.000825         206         4           sendto
  5.68    0.000784         392         2           close
  3.79    0.000524         262         2           socket
  2.54    0.000351         351         1           clone
  2.32    0.000321          80         4         1 futex
  2.19    0.000302          60         5           rt_sigprocmask
  1.01    0.000140          70         2           brk
  0.89    0.000123          41         3         3 openat
  0.76    0.000105         105         1           mprotect
  0.62    0.000085          85         1           ioctl
  0.45    0.000062          62         1           set_tid_address
  0.45    0.000062          62         1           tkill
  0.44    0.000061          61         1           clock_gettime
  0.41    0.000057          57         1           sched_getaffinity
  0.30    0.000041          41         1           getpid
------ ----------- ----------- --------- --------- ------------------
100.00    0.013812         131       105         4 total
```