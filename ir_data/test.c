
#include "test.h"

volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

uint8_t time_val;



void main(void)
{
    CLK_CKDIVR = 0x00; // Set the frequency to 16 MHz

    init_clock();

    //leds
    PD_DDR |= 0x01;
    PD_CR1 |= 0x01;
    PD_ODR |= 0x01;

    PC_DDR |= 0x60;
    PC_CR1 |= 0x60;
    PC_ODR |= 0x60;

    PB_DDR |= 0x07;
    PB_CR1 |= 0x07;
    PB_ODR |= 0x07;
    
    init_serial();

	__asm
	rim
	__endasm;


    // use test set command to test this
	while(1){
        time_val = TIM2_CNTRL>>2;
        if(time_val>=bval){
            PC_ODR |= 0x40;
        }else{
            PC_ODR &= ~0x40;
        }
        if(time_val>=rval){
            PC_ODR |= 0x20;
        }else{
            PC_ODR &= ~0x20;
        }
        if(time_val>=gval){
            PD_ODR |= 0x01;
        }else{
            PD_ODR &= ~0x01;
        }

        if(serial_data_ready_flag){
            if(serial_cmd ==0){
                bval=0;
                gval=0;
                rval=0;
            }else if(serial_cmd == 1){
                bval = serial_data[0];
            }else if(serial_cmd==2){
                gval = serial_data[0];
            }else if(serial_cmd==3){
                rval = serial_data[0];
            }
            serial_data_ready_flag=0;
        }

        if(comm_state==WAIT){
            PB_ODR = 0x06;
        }else if(comm_state==START){
            PB_ODR = 0x05;
        }else if(comm_state==DATA){
            PB_ODR = 0x03;
        }else if(comm_state==END_BYTE){
            PB_ODR = 0x01;
        }else if(comm_state==CMD_DLE){
            PB_ODR = 0x02;
        }else if(comm_state==DATA_DLE){
            PB_ODR = 0x04;
        }else{
            PB_ODR = 0x07;
        }
    }
}
