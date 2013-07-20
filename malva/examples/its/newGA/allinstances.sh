#!/bin/bash

for i in $(find ../instances -name "*.in")
do
	./MainSeq config.dat $i salida.out | grep "Solution:"
done

#find ../instances -name "*.in" | xargs ./MainSeq config.dat

