#!/bin/bash

g++ E.cpp -fsanitize=address,undefined -O3 -fsanitize=address,undefined -D_GLIBCXX_DEBUG -D_FORTIFY_SOURCE=2 --std=c++20 -o main

for i in `seq 1 10000`; do 

    echo $i 

    python gen_test.py > test.txt

    ./main < test.txt > output.txt || break
done
