#!/bin/bash

dd if=/dev/zero of=<fs-name> bs=nM count=n  #<rootfs-size = bs*ct>
mkfs.ext<n> -m 0 -F <fs-name>
mount -o loop <fs-name> /mnt/
chmod 777 <fs-name>