#!/bin/bash

#for循环的shell用法
set array
array=(1 3 5 7 9)
for ii in ${array[@]}
do
   echo $ii;
done

for((ii=0;ii<${#array[@]};ii++))
do
   echo ${array[${ii}]};
done
