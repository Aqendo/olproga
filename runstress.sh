#!/bin/bash
g++ main.cpp -o main
g++ slow.cpp -o slow
g++ testgen.cpp -o testgen

for i in `seq 1 10000`; do

    echo $i

    ./testgen > test.txt

    timeout 1s ./main < test.txt > output.txt
    ./slow < test.txt > answer.txt

    diff -rBNu output.txt answer.txt || break
done
