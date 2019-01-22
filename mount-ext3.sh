dd if=/dev/zero of=/tmp/disk_ext3.img bs=300M count=1
mkfs.ext3 -b 4096 /tmp/disk_ext3.img
sudo losetup /dev/loop15 /tmp/disk_ext3.img
sudo mkdir /mnt/ext3
sudo mount -t ext3 /dev/loop15 /mnt/ext3/