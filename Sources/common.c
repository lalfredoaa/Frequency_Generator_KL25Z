
#include "common.h"

void common_init(){
	SIM   = SIM_BASE_PTR;
	MCG   = MCG_BASE_PTR;
	
	UART0 = UART0_BASE_PTR;
	
	PORTA = PORTA_BASE_PTR;
	PORTB = PORTB_BASE_PTR;
	PORTC = PORTC_BASE_PTR;
	PORTD = PORTD_BASE_PTR;
	PORTE = PORTE_BASE_PTR;
	
	GPIOA   = PTA_BASE_PTR;
	GPIOB   = PTB_BASE_PTR;
	GPIOC   = PTC_BASE_PTR;
	GPIOD   = PTD_BASE_PTR;
	GPIOE   = PTE_BASE_PTR;
	
	TPM0  = TPM0_BASE_PTR;
	TPM1  = TPM1_BASE_PTR;
	TPM2  = TPM2_BASE_PTR;
	
	NVIC  = NVIC_BASE_PTR;
	
	ADC0 = ADC0_BASE_PTR;
	
	DAC0 = DAC0_BASE_PTR;
	
	LPTMR0 = LPTMR0_BASE_PTR;
}