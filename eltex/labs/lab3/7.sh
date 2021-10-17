#!/bin/bash
#Вывести три наиболее часто встречающихся слова из man по команде bash длиной не менее четырех символов.
man bash | grep -o '[a-zA-Z]\{4,\}' | sort | uniq -c | sort -nr | head -n 3
