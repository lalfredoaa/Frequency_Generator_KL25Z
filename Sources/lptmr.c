
#include "common.h"
#include "uart.h"

void lptmr_init(void){
	
	SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
	
	LPTMR0->PSR = 0x00000005;
	LPTMR0->CMR = 1000;			//count 1 sec
	LPTMR0->CSR = 0b01000001;
	
	NVIC_ISER = (1<<28);
}

void LPTimer_IRQHandler(){
	
	UART_status();
	LPTMR0_CSR |= (1<<7);
	
}
