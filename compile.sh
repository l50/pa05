#!/bin/bash

if [ "$1" == "compile" ]; then
  gcc -pthread -o race race.c
else
  for i in `seq 1 20`;
  do
    ./race
    printf "\n"
  done
fi

