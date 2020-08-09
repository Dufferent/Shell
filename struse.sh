#!/bin/bash

str_1="strcpy"
str_2="useful"

str_3="${str_1}${str_2}"
echo $str_3

str_3="${str_1:3}${str_2:1:3}"
echo $str_3
