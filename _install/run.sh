export LD_LIBRARY_PATH=/lib:$LD_LIBRARY_PATH
busybox ip link set dev lo up
./test
