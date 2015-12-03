sdcc -mstm8 --std-c99 -c serial.c
sdcc -mstm8 --std-c99 test.c serial.rel
stm8flash -c stlink -p stm8l051f3 -w test.ihx 

oh_shit.c is the fall-back file that runs using the original protocol (0 is blackout, 0x01-0x40 is red val, 0x41-0x80 is gval and 0x81-0xC0 is Bval
