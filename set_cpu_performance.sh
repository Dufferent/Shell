#!/bin/bash

#set cpu performance manual
array=(0 1 2 3)

for ii in ${array[@]}
do
	sudo /usr/bin/cpufreq-set -c ${ii} -g performance
done
