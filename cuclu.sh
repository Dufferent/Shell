#!/bin/bash

#加减乘除四则运算
#1.做加法
set num_1
set num_2
num_1=5
num_2=3
consequence=`expr $num_1 + $num_2`
echo $consequence

consequence=$[${num_1} + ${num_2}]
echo $consequence

consequence=$((${num_1} + ${num_2}))
echo $consequence

#2.做减法
consequence=`expr $num_1 - $num_2`
echo $consequence

consequence=$[${num_1} - ${num_2}]
echo $consequence

consequence=$((${num_1} - ${num_2}))
echo $consequence
#3.做乘法
consequence=`expr $num_1 \* $num_2`
echo $consequence

consequence=$[${num_1} * ${num_2}]
echo $consequence

consequence=$((${num_1} * ${num_2}))
echo $consequence
#4.做除法
consequence=`expr $num_1 / $num_2`
echo $consequence

consequence=$[${num_1} / ${num_2}]
echo $consequence

consequence=$((${num_1} / ${num_2}))
echo $consequence
#5.取余数
consequence=`expr $num_1 % $num_2`
echo $consequence

consequence=$[${num_1} % ${num_2}]
echo $consequence

consequence=$((${num_1} % ${num_2}))
echo $consequence

#6.浮点数`bc`
#操作数放入bc必须事先用set定义
echo "scale=3;${num_1}/${num_2}"|bc
consequence=`echo "scale=3;${num_1}/${num_2}"|bc`
echo $consequence

echo "scale=3;${consequence}-1"|bc
