#include "error.h"

void error_block(){
   while(1){
       while(clock()<30000){
           PB_ODR=0x07;
           PD_ODR=0x00;
       }
       while(clock()>30000){
           PB_ODR=0x06;
           PD_ODR=0x01;
       }
   }
}
