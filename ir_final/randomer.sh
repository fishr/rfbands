#!/bin/bash

rand="$(od -vAn -N4 -tu4 < /dev/urandom)"

cmd_prog="sdcc -mstm8 --std-c99 -DRANDOM_SEED="$(tr -d '[:space:]'<<<$rand)" test.c serial.rel"
echo $cmd_prog
