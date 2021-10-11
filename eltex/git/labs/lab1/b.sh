#!/bin/bash
if [[ $1 -ge $2 ]] #если первый элемент больше или равен второму
then
echo $1 > outb
else
echo $2 > outb
fi 
