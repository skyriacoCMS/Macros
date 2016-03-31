#!/bin/bash

FILE=EMPTY.txt

k=1
echo " read line of file"
while read line;do
    echo $line
    ((k++))
done < $FILE