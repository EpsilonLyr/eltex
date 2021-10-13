#!/bin/bash

cat /var/log/* | grep -a syslog > errors.log
grep -a -E "^.*\/([a-zA-Z0-9.]+\/)+" "errors.log" 

