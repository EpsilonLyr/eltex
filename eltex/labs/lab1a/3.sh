#!/bin/bash
value=0

echo "введите 1, чтобы открыть nano"
echo "введите 2, чтобы открыть vi"
echo "введите 3, чтобы открыть firefox"
echo "введите любой другой символ, чтобы выйти"
read value
case $value in
1)
exec nano #запуск программы nano
;;
2)
exec vi
;;
3)
exec firefox
;;
esac
exit 0 #завершаем сценарий со статусом выхода 0
