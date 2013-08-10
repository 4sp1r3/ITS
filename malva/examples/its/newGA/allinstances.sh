#!/bin/bash

for i in $(find ../instances -name "*.in" | sort)
do
	./MainSeq config.dat $i salida.out | grep -E "(F=|Solution:)"
done

#find ../instances -name "*.in" | xargs ./MainSeq config.dat

