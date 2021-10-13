#!/bin/bash
man bash | grep -o '[a-zA-Z]\{4,\}' | sort | uniq -c | sort -nr | head -n 3
