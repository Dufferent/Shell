#!/bin/bash

#while循环的使用
val=$1
while [ ${val} -gt 0 ]
do
    echo $val
    val=$[$val-1]
done
set array
array=(2 4 6 8 10)
set ii
ii=${#array[@]}
while [ ${ii} -gt 0 ]
do
    echo ${array[$[$ii-1]]};
    ii=$[$ii-1];
done
