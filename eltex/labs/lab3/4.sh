#!/bin/bash

#Найти в директории /bin все файлы, которые являются сценариями, и вывести на экран  полное имя файла
#с интерпретатором, наиболее часто используемым в этих сценариях (только полное имя файла).
string=`file /bin/* | grep ' script' | cut -d : -f 1 | xargs -n 1 head -n 1 | sort | uniq -c | sort -rn | head -n 1`
interpretator="#${string#*\#}"
grep -lwr '/bin/' -e $interpretator
