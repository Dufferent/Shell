#!/bin/bash
#1.if语句的字符串比较
if [ $1 = "xny" ];then
	printf "cmd1 equa cmd2!\r\n"
else
	printf "cmd1 unfair cmd2!\r\n"
fi
#2.if语句的单个字符比较
if [ $2 = 'y' ];then
	printf "yes!\r\n"
else
	printf "no!\r\n"
fi
#3.if语句的数值比较
#-eq相等 -gt大于 -lt小于 -ge大于等于 -le小于等于 -ne不等于
if [ $3 -eq 7 ];then
	printf "num correct!\r\n"
else
	printf "not find!\r\n"
fi
#4.else if语句
if [ $4 -eq 5 ];then
	echo -e "run if"
elif [ $4 -gt 6 ];then
	echo -e "run else if"
fi


