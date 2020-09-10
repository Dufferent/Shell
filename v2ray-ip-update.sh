#!/bin/bash

#v2ray客户端配置跟新脚本-一键运行
wget --ca-certificate=ca-bundle.crt -c https://gitlab.com/free9999/ipupdate/-/raw/master/v2rayN/guiNConfig.json
cat ./guiNConfig.json |grep -w address > ./change-msg
cat ./guiNConfig.json |grep -w id >> ./change-msg
cat ./guiNConfig.json |grep -w port >> ./change-msg

sudo cp /etc/v2ray/config.json ./
sudo chown xny ./config.json
sudo chmod +rw ./config.json

#调用程序生成config.json
./autochange
#清屏
printf "\033c"

sudo mv ./config.json /etc/v2ray/config.json

#清理文件
rm ./change-msg ./guiNConfig.json -rf

#重启服务
sudo service v2ray restart
