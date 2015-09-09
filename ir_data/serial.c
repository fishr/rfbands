
#include "serial.h"

volatile extern bit serial_data_ready_flag = 0;
volatile extern uint8_t serial_cmd = 0;
volatile extern uint8_t serial_data[MAX_SERIAL_BUFF];
volatile static comm_state_t comm_state = WAIT;

void init_serial_clock(){
    //USART1_BRR2 = SERIAL_CLK_HIGH;
    //USART1_BRR1 = SERIAL_CLK_LOW;
    USART1_BRR2 = 0x35;
    USART1_BRR1 = 0x41;
}

void init_serial(){
    PA_DDR &= ~0x08;
    PA_CR1 |= 0x08;
    PA_CR2 &= ~0x08;

    SYSCFG_RMPCR1 |= 0x10;
    
    CLK_PCKENR1 |= PCKEN_USART1;

    //USART1_CR1 |= USART_M|USART_PCEN;
    //USART1_CR1 &= ~USART_PS;
    
    init_serial_clock();
    
    USART1_CR2 |= USART_REN|USART_RIEN;
}

void disable_serial(){
    USART1_CR2 &= (~USART_REN)&(~USART_RIEN);
    SYSCFG_RMPCR1 &= ~(0x10);
    CLK_PCKENR1 &= ~(PCKEN_USART1);
}

void serial_isr(void) __interrupt 28
{
    uint8_t raw_data = USART1_DR;

    if(USART1_SR & USART_ERROR){
        comm_state = ERROR;
    }else if(USART1_SR & USART_RXNE){
        switch(comm_state){
            case WAIT:
                if(raw_data==COMM_START_BYTE){
                    comm_state = START;
                }
                break;
            case START:
                if(raw_data==COMM_DLE){
                    comm_state = CMD_DLE;
                }else if(raw_data==NULL_INDICATOR){
                    serial_cmd = 0;
                    comm_state = DATA;
                }else if(raw_data==COMM_START_BYTE||raw_data==COMM_END_BYTE){
                    comm_state=ERROR;
                }else{
                    serial_cmd = raw_data;
                    comm_state = DATA;
                }
                break;
            case CMD_DLE:
                serial_cmd=raw_data;
                comm_state = DATA;
                break;
            case DATA:
                if(raw_data==COMM_DLE){
                    comm_state = DATA_DLE;
                }else if(raw_data==NULL_INDICATOR){
                    serial_data[0] = 0;
                    comm_state = END_BYTE;
                }else if(raw_data==COMM_START_BYTE||raw_data==COMM_END_BYTE){
                    comm_state=ERROR;
                }else{
                    serial_data[0] = raw_data;
                    comm_state = END_BYTE;
                }
                break;
            case DATA_DLE:
                serial_data[0]=raw_data;
                comm_state = END_BYTE;
                break;
            case END_BYTE:
                if(raw_data==COMM_END_BYTE){
                    serial_data_ready_flag = 1;
                    comm_state = WAIT;
                }else{
                    comm_state = ERROR;
                }
                break;
            default:
                ERROR_COMM();
                break;
        }
    }else{
        comm_state == ERROR;
    }
    if(comm_state == ERROR){
        ERROR_COMM();
    }
}

/*---------------------DEPRECATED-----------------------------

static comm_state_h state = WAIT;
static uint16_t time = 0;
static bit new_serial = 0;

void old_init_serial_clock(){
    // Configure serial timer
    // hits 2560 in 320us
    TIM3_PSCR = 0x01;
    TIM3_CNTRH = 0;
    TIM3_CNTRL = 0;
}

void old_init_serial_pin(){
	//configure interrupts
	PC_DDR &= 0xFF^(1<<4);
	PC_CR1 &= 0xFF^(1<<4);
	EXTI_CR2 |= 0x02; // initially detect falling edges

	//ENGAGE
	PC_CR2 |= 1<<4;
}

*
 * need a start bit so we force things low to start timings!
 * every message is padded, account for this in placement
*


void old_serial_isr (void) __interrupt 12
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

void old_serial_update(){
    if(new_serial){
        pass
    }
}

-----------------------------END DEPRECATED--------------------------*/
