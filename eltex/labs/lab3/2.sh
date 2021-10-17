#!/bin/bash
#Создать full.log, в который вывести строки файла /var/log/rhsm/rhsm.log, содержащие предупреждения и информационные сообщения,
#заменив маркеры предупреждений и информационных сообщений на слова Warning: и Information:,
#чтобы в получившемся файле сначала шли все информационные сообщения, а потом все предупреждения. Вывести этот файл на экран.
grep -a -E  "\\(WW\\)" /var/log/rhsm/rhsm.log | sed -E "s/$war/Warning: /" > full.log
grep -a -E  "\\(II\\)" /var/log/rhsm/rhsm.log | sed -E "s/$inf/Information: /" >> full.log
