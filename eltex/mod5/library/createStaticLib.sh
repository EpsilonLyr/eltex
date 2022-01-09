#!/bin/bash
gcc -c f1.c f2.c
ar rc libstatic.a f1.o f2.o
ranlib libstatic.a
gcc main.c -L. -lstatic -o result

