
#include "serial.h"

static comm_state_h state = WAIT;
static uint16_t time = 0;
static bit new_serial = 0;


void init_serial_clock(){
    // Configure serial timer
    // hits 2560 in 320us
    TIM3_PSCR = 0x01;
    TIM3_CNTRH = 0;
    TIM3_CNTRL = 0;
}

void init_serial_pin(){
	//configure interrupts
	PC_DDR &= 0xFF^(1<<4);
	PC_CR1 &= 0xFF^(1<<4);
	EXTI_CR2 |= 0x02; // initially detect falling edges

	//ENGAGE
	PC_CR2 |= 1<<4;
}

/*
 * need a start bit so we force things low to start timings!
 * every message is padded, account for this in placement
*/


void serial_isr (void) __interrupt 12
{
    switch(state){
        case WAIT:
            state = START;
            TIM3_CNTRH = 0;
            TIM3_CNTRL = 0;
            TIM3_CR1 |= 1<<TIM_CR1_CEN;
            break;
        case START:
            TIM3_CR1 &= 0xFF^(1<<TIM_CR1_CEN);
            uint8_t low = TIM3_CNTRL;
            time  = TIM3_CNTRH<<8+low;
            new_serial = 1;
      
            uint16_t error = time % CLK_COUNTS_PER_BIT;
            uint16_t allowed_error = time>>ALLOWED_ERROR;
            uint8_t ones = 0;
            if(error<allowed_error){
                ones = (uint8_t) time/CLK_COUNTS_PER_BIT;
            }else if(error>CLK_COUNTS_PER_BIT-ALLOWED_ERROR)){
                ones = (uint8_t) time/CLK_COUNTS_PER_BIT + 1;
            }else{
                state=ERROR;
                break;
            }

            break;
    }
    EXTI_SR1 |= 1<<4;
}

void serial_update(){
    if(new_serial){
        pass
    }
}
