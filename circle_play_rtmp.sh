#!/bin/bash

#mplayer循环播放
for ((i=0;i<$1;i++))
do
for name in `ls /home/xny/Music`
do
	ffmpeg -re -i /home/xny/Music/${name} -acodec aac -vn -f flv rtmp://127.0.0.1:1935/live/xny;
done
done
