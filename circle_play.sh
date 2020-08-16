#!/bin/bash

#mplayer循环播放
for ((i=0;i<$1;i++))
do
for name in `ls /home/xny/Music`
do
	mplayer /home/xny/Music/${name};
done
done
