#!/bin/bash
gcc -fPIC -c f1.c f2.c
gcc -shared -o libdynamic.so f1.o f2.o
gcc main_v2.c -o resultDyn_v2 -ldl


