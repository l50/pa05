#!/bin/bash

gcc simrwsimple.c -lm -lpthread -o simrw
chmod +x simrw
./simrw
