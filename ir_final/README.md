sdcc -mstm8 --std-c99 -c serial.c
sdcc -mstm8 --std-c99 -c io.c
sdcc -mstm8 --std-c99 -c hsv2rgb.c

sdcc -mstm8 --std-c99 -DRANDOM_SEED=1234567 -DKRESGE_ROW=1 final.c serial.rel io.rel hsv2rgb.rel
stm8flash -c stlink -p stm8l051f3 -w final.ihx 

oh_shit.c is the fall-back file that runs using the original protocol (0 is blackout, 0x01-0x40 is red val, 0x41-0x80 is gval and 0x81-0xC0 is Bval


Special Chars:
#define SERIAL_START_BYTE 55
#define SERIAL_END_BYTE 43
#define SERIAL_DLE 47
#define SERIAL_NULL_INDICATOR 53

These four bytes have special meanings, and using them between the 2 start bytes and the end byte will cause the packet to be dropped if they are unescaped.
Null Indicator is a slight exception, as it will be turned into a 0 if it is unescaped, for compatibility with systems that depend on 0 to terminate strings.

if you need to send one of these values as the message function or data, insert a SERIAL_DLE before it.  If you need an R value of 55, put 47,55 in you packet.  The packet will be longer than the input to the function, but all the first DLE characters get removed before passing on

EXAMPLE PACKETS (in decimal):
{55,55,255,43}//as close to a system reset as I could do
{55,55,0,1,2,3,43} //function 0 with input (1,2,3)
{55,55,0,53,53,53,43} //equivalent to sending {55,55,0,0,0,0,43}
{55,55,0,47,53,53,53,43} //the first 53 stays a 53 because of the escape, so function 0 with (53,0,0)
{55,55,0, 47,47,47,47,47,47,43} // turns into func 0 with (47, 47, 47)

#Functions
0. set RGB globally (r,g,b) colors 0-255								GOOD
1. set row (r,g,b,row)  colors 0-255, rows unknown limits						GOOD
2. random twinkle fixed color (r,g,b,probability) all full bytes 0-253               		        GOOD?
3. random color random twinkle (probability) 0-255   							GOOD?
4. random color of fixed brightness (brightness) 0-255							GOOD
