#!/bin/bash
gcc -c 2labPage.c -o 2labPage.o
gcc commonFunctions.o 2labPage.o -o 2labPage
