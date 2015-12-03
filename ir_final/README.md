sdcc -mstm8 --std-c99 -c serial.c
sdcc -mstm8 --std-c99 test.c serial.rel
stm8flash -c stlink -p stm8l051f3 -w test.ihx 
