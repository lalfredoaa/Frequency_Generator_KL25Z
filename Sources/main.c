
#include "common.h"
#include "uart.h"
#include "buttons.h"
#include "adc.h"
#include "dac.h"
#include "lptmr.h"


int main(void)
{
	common_init();
	NVIC->ICPR = 0; 			//Clear pending interrupts
	UART0_init();
	buttons_init();
	ADC0_init();
	DAC0_init();
	timer_init();
	init_arrays();
	lptmr_init();
	
	for (;;) {			
		
	}
}
