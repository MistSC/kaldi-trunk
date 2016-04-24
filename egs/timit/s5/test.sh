#!/bin/bash
aa=(1 2 3 4 5)
echo ${aa[0]}
ll=${#aa[*]}
echo $(((${#aa[*]}-1)/2))
