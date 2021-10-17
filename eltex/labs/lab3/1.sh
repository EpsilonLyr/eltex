#!/bin/bash

#Создать файл errors.log, в который поместить все строки из всех доступных для чтения файлов директории /var/log/, 
#содержащие  последовательности символов syslogd,
#без указания имени файла, в котором встретилась строка. Вывести на экран те строчки из получившегося файла,
#которые содержат полные имена каких-либо файлов.

cat /var/log/* | grep -a syslog > errors.log
grep -a -E "^.*\/([a-zA-Z0-9.]+\/)+" "errors.log" 

