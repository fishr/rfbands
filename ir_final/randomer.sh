#!/bin/bash

rand="$(od -vAn -N2 -tu2 < /dev/urandom)"

cmd_prog="sdcc -mstm8 --std-c99 -DRANDOM_SEED="$(tr -d '[:space:]'<<<$rand)" -DKRESGE_ROW=$1 final.c io.rel hsv2rgb.rel serial.rel"
echo $cmd_prog

eval $cmd_prog

#$flasher =  "/usr/bin/stm8flash -c stlink -p stm8l051f3 -w final.ihx"
#echo $flasher

#eval $flasher
