#!/bin/sh

#New Disk addition

#1.step
#   sudo fdisk -l  或者 df -h
#   查看新的硬盘的详细信息
df -h
#如下
#Filesystem                   Size  Used Avail Use% Mounted on
#udev                         7.8G     0  7.8G   0% /dev
#tmpfs                        1.6G  9.3M  1.6G   1% /run
#/dev/mapper/ubuntu--vg-root  1.2T  6.1G  1.1T   1% /
#/dev/sda1                    981.5G   0  985.5G 0% /media/xny
#   ......
#/dev/nvme0n1p2               721M  144M  541M  22% /boot
#/dev/nvme0n1p1               511M  3.7M  508M   1% /boot/efi

#2.step
#   如果是新硬盘直接分区
#   sudo fdisk /dev/sda <d n w><删除分区 创建分区 写入盘符>
#   *如果硬盘没有分区表用g G o s 创建你需要的分区表
#   回到terminal
echo "请输入新硬盘的分区名称<Filesystem>"
read disk-name 
sudo pvcreat ${disk-name}  #/dev/sda1 <disk-name>
sudo pvdisplay   #"回显"
#  --- Physical volume ---
#  PV Name               /dev/nvme0n1p3
#  VG Name               ubuntu-vg
#  PV Size               231.67 GiB / not usable 2.00 MiB
#  Allocatable           yes (but full)
#   ......
#  PV UUID               SNyvVA-DTPe-aaoe-1Bh3-jYjs-TkpO-I3v92u
#   
#  --- Physical volume ---
#  PV Name               /dev/sda1
#  VG Name               ubuntu-vg
#  PV Size               931.51 GiB / not usable 4.69 MiB
#  Allocatable           yes (but full)
#    ......
#  PV UUID               Ou1Ffn-m99D-mMCL-qjlL-JSEO-9INC-Dryydr
echo "请输入需要扩充分区的Vg-Name"
read VG-NAME 

#3.扩展分区
sudo vgextend ${VG-NAME} ${disk-name}
sudo lvdisplay #"回显"

#4.扩充你需要的分区
#  --- Logical volume ---
#  LV Path                /dev/ubuntu-vg/root
#  LV Name                root
#  VG Name                ubuntu-vg
#  LV UUID                2aCUaE-D9Kh-bfjF-bh9X-HJId-RAno-sYa3h3
#  LV Write Access        read/write
#  LV Creation host, time ubuntu, 2020-08-13 13:38:30 +0800
#  LV Status              available
#  ...
#  LV Size                1.13 TiB
#  ......
echo "请输入LV_PATH"
read LV_PATH
sudo lvextend ${LV_PATH} ${disk-name}

#5.重新判定扩充分区大小
resize2fs ${LV_PATH}
df -h