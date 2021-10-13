#!/bin/bash
grep -s -h -r -E -o -a '[a-zA-Z0-9._]+@[a-zA-Z]+(\.[a-zA-Z]+)+' /etc | awk '{printf ("%s, ", $1)}' > emails.lst
