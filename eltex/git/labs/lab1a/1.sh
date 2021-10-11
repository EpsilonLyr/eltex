#!/bin/bash
value=''
str=''
while [ "$value" != 'q' ] #пока не введем q продолжаем цикл
do
read value
str+="$value" #конкатенация вводимых значений в одну строку
done
echo $str
