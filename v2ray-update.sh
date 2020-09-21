#!/bin/bash

#下载配置文件
wget --ca-certificate=ca-bundle.crt -c https://gitlab.com/free9999/ipupdate/-/raw/master/v2rayN/config.json
changeconf
sudo mv ./config.json /etc/v2ray/config.json
#重启v2ray
sudo service v2ray restart
#查看v2ray状态
service v2ray status
