sdcc -mstm8 --std-c99 -c serial.c
sdcc -mstm8 --std-c99 -DRANDOM_SEED=1234567 test.c serial.rel
stm8flash -c stlink -p stm8l051f3 -w test.ihx 

oh_shit.c is the fall-back file that runs using the original protocol (0 is blackout, 0x01-0x40 is red val, 0x41-0x80 is gval and 0x81-0xC0 is Bval


#Functions
1. set row (r,g,b,row)  colors 0-255, rows unknown limits
2. set RGB globally (r,g,b) colors 0-255
3. random twinkle fixed color breathing (r,g,b,probability) all full bytes 0-255
4. random color random twinkle (probability) 0-255
5. random color of fixed brightness (brightness) 0-255
6. random twinkle no breathe  (rgb, prob)
7. random color random twinkle no breathe (prob)
