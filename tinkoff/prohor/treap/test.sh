#!/bin/bash
for i in $(seq 0 1000000)
do
    TEST=$(./testgen)
    RES1=$(./main <<< $TEST)
    RES2=$(./slow <<< $TEST)
    if [[ "$RES1" != "$RES2" ]]; then
        echo $TEST
        echo $RES1
        echo $RES2
        exit
    fi
done
