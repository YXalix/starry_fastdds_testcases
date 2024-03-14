# cp ~/riscv64-linux/riscv64-lp64d--glibc--stable-2024.02-1/riscv64-buildroot-linux-gnu/sysroot/lib/* -av ./busybox/_install/lib/
# cp ~/riscv64-linux/riscv64-lp64d--glibc--stable-2024.02-1/riscv64-buildroot-linux-gnu/sysroot/usr/lib/* -av ./busybox/_install/usr/lib/

rm disk.img
dd if=/dev/zero of=disk.img bs=3M count=240
#mkfs.vfat -F 32 disk.img
mkfs.ext4 disk.img
mkdir -p mnt
sudo mount disk.img mnt
# 根据命令行参数生成对应的测例
sudo cp -r ./_install/* ./mnt/
sudo umount mnt
rm -rf mnt
sudo chmod 777 disk.img

# VMN=1
# qemu-system-x86_64 \
#     -machine pc,accel=kvm,kernel_irqchip \
#     -enable-kvm \
#     -bios OVMF.fd \
#     -smp sockets=1,cpus=4,cores=2 -cpu host \
#     -m 1024 \
#     -vga none -nographic \
#     -drive file="$IMAGE",if=virtio,aio=threads,format=raw \
#     -netdev user,id=mynet0,hostfwd=tcp::${VMN}0022-:22,hostfwd=tcp::${VMN}2375-:2375 \
#     -device virtio-net-pci,netdev=mynet0 \
#     -netdev socket,id=vlan,mcast=230.0.0.1:1234 \
#     -device virtio-net-pci,netdev=vlan \
sudo qemu-system-riscv64 -nographic -m 2G -smp 1 \
    -machine virt -bios default -kernel ./Image \
     -append "root=/dev/vda rw console=ttyS0 init=/bin/busybox sh" \
     -device virtio-blk-device,drive=disk0 -drive id=disk0,if=none,format=raw,file=disk.img \
     -device virtio-net-device,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5555-:5555,hostfwd=udp::5555-:5555 \
     -netdev socket,id=vlan,mcast=230.0.0.1:1234 -device virtio-net-pci,netdev=vlan
# -drive file=disk.img,format=raw,id=hd0 \


# -device virtio-blk-device,drive=hd0 -device virtio-net,netdev=network0 -netdev tap,id=network0,ifname=tap0,script=no,downscript=no
# -netdev tap,id=net0,ifname=tap0,script=no,downscript=no -device virtio-net,netdev=net0,mac=A7:AD:BE:EF:CA:FE
# -netdev user,id=mynet0,hostfwd=tcp::10022-:22,hostfwd=tcp::12375-:2375 -device virtio-net-pci,netdev=mynet0 -netdev socket,id=vlan,mcast=230.0.0.1:1234 -device virtio-net-pci,netdev=vlan


# sudo /home/tom/qemu-on-arm32/qemu/qumu-2.12.0/bin/qemu-system-arm -M vexpress-a9 -m 512M -kernel zImage -nographic -append "root=/dev/mmcblk0 console=ttyAMA0" -sd arm32_rootfs.ext4 -net nic,macaddr=00:aa:00:60:00:01,model=lan9118 -net tap,ifname=tap0,script=no

# 执行后先     export LD_LIBRARY_PATH=/lib:$LD_LIBRARY_PATH
# 启用网络接口: ip addr add 192.168.1.2/24 dev eth0
#             ip link set dev eth0 up
#             ip link set dev sit0 up