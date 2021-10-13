#!/bin/bash
grep -a -E  "\\(WW\\)" /var/log/rhsm/rhsm.log | sed -E "s/$war/Warning: /" > full.log
grep -a -E  "\\(II\\)" /var/log/rhsm/rhsm.log | sed -E "s/$inf/Information: /" >> full.log
