sdcc -mstm8 --std-c99 -c serial.c
sdcc -mstm8 --std-c99 -c io.c
sdcc -mstm8 --std-c99 -c hsv2rgb.c

sdcc -mstm8 --std-c99 -DRANDOM_SEED=1234567 -DKRESGE_ROW=1 final.c serial.rel io.rel hsv2rgb.rel
stm8flash -c stlink -p stm8l051f3 -w final.ihx 

oh_shit.c is the fall-back file that runs using the original protocol (0 is blackout, 0x01-0x40 is red val, 0x41-0x80 is gval and 0x81-0xC0 is Bval


#Functions
0. set RGB globally (r,g,b) colors 0-255								GOOD
1. set row (r,g,b,row)  colors 0-255, rows unknown limits						GOOD
2. random twinkle fixed color (r,g,b,probability) all full bytes 0-253               		        GOOD?
3. random color random twinkle (probability) 0-255   							GOOD?
4. random color of fixed brightness (brightness) 0-255							GOOD
