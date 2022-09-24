#!/bin/bash
NAME=2

for data in $(cat $(dirname $0)/$NAME.data | tr ' ' '_')
do
	data=$(echo $data | tr '_' ' ')
	echo "Input=$data"
	printf "Output="
	printf "$data\n" EOF | $(dirname $0)/../bin/build-$(echo $NAME)-Desktop-Debug/$NAME  
	printf "\n"
done