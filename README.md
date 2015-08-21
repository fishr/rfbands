stm8flash -c stlink -p stm8l051f3 -w test.ihx

sdcc -mstm8 --std-c99 test.c
