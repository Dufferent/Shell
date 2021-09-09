#!/bin/bash

echo "Qemu Net Configure DeInit..."
sudo ifconfig tap0 down
sudo ifconfig br0 down
sudo ip tuntap del tap0 mod tap
sudo brctl delbr br0
sudo iptables -t nat -D POSTROUTING 1
read -p "Press AnyKey to Continure..."
exit 0
