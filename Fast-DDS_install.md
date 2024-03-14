# Fast-DDS 从源码编译安装

## 相关链接
[arceos文档](https://rcore-os.cn/arceos-tutorial-book/ch01-04.html)

[编译相关blog](https://blog.csdn.net/qq_41281601/article/details/122827385)

[Starry项目地址](https://github.com/Arceos-monolithic/Starry)
## Fast-DDS 编译
在linux环境下编译安装Fast-DDS, 需要安装以下packages:
1. foonathan_memory_vendor: 一个STL兼容的C++内存分配器库
2. fastcdr: 一个根据标准CDR序列化机制进行序列化的C++库
3. fastrtps: the core library of _eProsima Fast DDS_ library
### Requirements
```shell
# Cmake, g++, wget and git
sudo apt install cmake g++ wget git
# 为了能跨平台编译我们需要针对riscv64的g++
# 下载交叉编译工具链源码
git clone https://github.com/richfelker/musl-cross-make.git
cd musl-cross-make
# 修改config.mak.dist中在设置
# TARGET = riscv64-linux-musl
# 修改litecross/Makefile的第227行为
# cd obj_musl && ../src_musl/configure $(FULL_MUSL_CONFIG) --enable-debug
make TARGET=riscv64-linux-musl
cd build/local/riscv64-linux-musl
make install OUTPUT={path}
# 将/riscv64-linux-musl/bin 添加到PATH
vim ~/.bashrc
export PATH={location of here}/riscv64-linux-musl/bin:$PATH
```

### Dependencies
1. Asio
2. TinyXML2
3. OpenSSL
4. Libp11
5. SoftHSM
6. Gtest
7. XML validation tool

### Cmake installation default
```CMake
# 将以下的内容填入CMakeLists.txt
set(CMAKE_CXX_COMPILER riscv64-linux-musl-g++)
set(CMAKE_C_COMPILER riscv64-linux-musl-gcc)
# 配置系统路径
set(CMAKE_SYSROOT /home/nashzhou/Fast-DDS/install)
#配置库文件头文件搜索路径
set(CMAKE_FIND_ROOT_PATH /home/nashzhou/Fast-DDS/install)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

**Asio**
```shell
# 下载Asio源码
# [asio C++ library download | SourceForge.net](https://sourceforge.net/projects/asio/)
tar -xvf asio-1.28.1.tar.gz asio
cd asio-1.28.1
# --host指定交叉编译的平台,
# --prefix指定安装目录
./configure --host=riscv64-linux-musl --prefix=/home/nashzhou/Fast-DDS/install
make
make install

# 如果出现linux/version.h 文件找不到的情况
# 可以在 path/musl-cross-make/linux-headers-4.19.88-1/generic/include中找到对应文件
# 将include整个文件夹的内容复制到riscv64-linux-musl/riscv64-linux-musl/include
cp -r ~/dev/musl-cross-make/linux-headers-4.19.88-1/generic/include ~/dev/riscv64-linux-musl/riscv64-linux-musl/include
```

TinyXML2
```shell
# 下载tinyxml2源码
git clone https://github.com/leethomason/tinyxml2.git
cd tinyxml2/
# 修改CMakeLists.txt, 参考 Cmake installation default
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS/install -DBUILD_SHARED_LIBS=OFF
cmake --build . --target install
```

**Foonathan memory**
```shell
cd ~/Fast-DDS
git clone https://github.com/eProsima/foonathan_memory_vendor.git
mkdir foonathan_memory_vendor/build
cd foonathan_memory_vendor/build
# 修改CMakeLists.txt, 在CMAKE_ARGS下面传递参数
	-DCMAKE_CXX_COMPILER=riscv64-linux-musl-g++
	-DCMAKE_C_COMPILER=riscv64-linux-musl-gcc
	-DCMAKE_SYSROOT=/home/nashzhou/Fast-DDS/install
	-DCMAKE_FIND_ROOT_PATH=/home/nashzhou/Fast-DDS/install
	-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER
	-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY
	-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY
	
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS/install -DBUILD_SHARED_LIBS=OFF 
# 如果执行以下步骤卡在git clone步骤, 可以考虑clone镜像地址, 或者科学办法
cmake --build . --target install
```
Fast CDR
```shell
cd ~/Fast-DDS
git clone https://github.com/eProsima/Fast-CDR.git
mkdir Fast-CDR/build
cd Fast-CDR/build
# 修改CMakeLists.txt, 参考 Cmake installation default
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS/install -DBUILD_SHARED_LIBS=OFF
cmake --build . --target install
```
Fast-DDS
```shell
cd ~/Fast-DDS
git clone https://github.com/eProsima/Fast-DDS.git
# 修改CMakeLists.txt, 参考 Cmake installation default
# 修改./test/CMakeLists.txt, 启用PERFORMANCE_TESTS的编译
# PERFORMANCE_TESTS=ON
# 在./test/performance/latency/CMakeLists.txt中添加全静态链接参数
# set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")

mkdir Fast-DDS/build
cd Fast-DDS/build
cmake ..  -DCMAKE_INSTALL_PREFIX=~/Fast-DDS/install -DBUILD_SHARED_LIBS=OFF
cmake --build . --target install
```