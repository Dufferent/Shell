#!/bin/bash

echo "Qemu Net Configure..."
sudo brctl addbr br0
sudo ip tuntap add tap0 mod tap
sudo brctl addif br0 tap0
sudo ifconfig br0 192.168.179.1
sudo ifconfig br0 up
sudo ifconfig tap0 up
# sudo iptables -t nat -A POSTROUTING -s 192.168.179.0/24 -j SNAT 192.168.10.102
sudo iptables -t nat -A POSTROUTING -s 192.168.179.0/24 -o ens33 -j MASQUERADE
read -p "Press AntKey to Continue..."
exit 0
