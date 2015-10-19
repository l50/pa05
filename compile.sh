#!/bin/bash

gcc -g -pthread -o race race.c
for i in `seq 1 20`;
do
    # ./a.out
    ./race
    printf "\n"
done

