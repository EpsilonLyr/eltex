#!/bin/bash
if [[ $1 == $2 ]] #если строки равны
then
echo "строки равны" > outa
else
echo "строки не равны" > outa
fi
