#!/bin/bash
dirpath=$(dirname $(readlink -e $0)) #получаем из относительного адреса абсолютный и отсекаем имя файла
if [[ $dirpath ==  "/home/$USER" ]] #если полученная строка - это адрес домашнего каталога  
then echo $dirpath #то выводим адрес домашнего каталога
exit 0
fi
echo "скрипт не в домашней директории"
exit 1
