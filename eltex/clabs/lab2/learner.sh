#!/bin/bash
gcc -c commonFunctions.c -o commonFunctions.o
gcc -c 2labLearner.c -o 2labLearner.o
gcc commonFunctions.o 2labLearner.o -o 2labLearner
