#!/bin/bash
answer=0
param="a"

while ! [[ $answer -eq 4 ]]
do

echo "введите 1, чтобы сделать бэкап файла"
echo "введите 2, чтобы восстановить файл"
echo "введите 3, чтобы посмотреть, какие файлы можно восстановить"
echo "введите 4, чтобы чтобы выйти"
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
3)
 exec ./availebleFilesForBackup
;;
esac
done
