dd if=/dev/zero of=/tmp/disk.img bs=300M count=1
mkfs.nilfs2 -B 256 /tmp/disk.img
#sudo losetup /dev/loop14 /tmp/disk.img
losetup -fP /tmp/disk.img
losetup -a
sudo mkdir /mnt/nilfs
sudo mount -t nilfs2 /dev/loop14 /mnt/nilfs/