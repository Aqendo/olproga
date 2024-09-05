#!/bin/bash
CFLAGS="-O3"

ulimit -s unlimited
g++ $CFLAGS testgen.cpp -o testgen
g++ $CFLAGS main.cpp -o main
i=0
echo "all good"
while true
do
    i=$((i+1))
    echo $i
    ./testgen $i &> test.txt

    ./main < test.txt &> output.txt
    python my.py < test.txt &> answer.txt

    diff output.txt answer.txt || break
done
