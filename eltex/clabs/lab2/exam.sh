#!/bin/bash
gcc -c commonFunctions.c -o commonFunctions.o
gcc -c 2labExam.c -o 2labExam.o
gcc commonFunctions.o 2labExam.o -o 2labExam
