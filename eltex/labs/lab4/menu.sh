#!/bin/bash
answer=0
param="a"

while ! [[ $answer -eq 3 ]]
do

echo "введите 1, чтобы сделать бэкап файла"
echo "введите 2, чтобы восстановить файл"
echo "введите 3, чтобы чтобы выйти"
read answer 
case $answer in
1)
  echo "введите имя файла"
  read param
  exec ./remftrash $param  
;;
2)
  echo "введите имя файла"
  read param
  exec ./unftrash $param  
;;
esac
done
