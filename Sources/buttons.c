
#include "common.h"
#include "buttons.h"
#include "uart.h"

void buttons_init(void){
	//clock to port A is already enabled by UART0_init();
	NVIC->ISER |= (1<<30); 				//enable interruption to detect button pressed
	
	//make pins GPIO with pullup resistor and Vcc inside
	PORTA->PCR[12] |= PORT_PCR_PE_MASK | PORT_PCR_MUX(1) | PORT_PCR_IRQC(10);
	PORTA->PCR[5] |= PORT_PCR_PE_MASK | PORT_PCR_MUX(1) | PORT_PCR_IRQC(10);
	PORTA->PCR[16] |= PORT_PCR_PE_MASK | PORT_PCR_MUX(1) | PORT_PCR_IRQC(10);
	PORTA->PCR[17] |= PORT_PCR_PE_MASK | PORT_PCR_MUX(1) | PORT_PCR_IRQC(10);
	
	//make pins inputs
	GPIOA->PDDR &= ~(1<<12);
	GPIOA->PDDR &= ~(1<<5); 
	GPIOA->PDDR &= ~(1<<16); 
	GPIOA->PDDR &= ~(1<<17);
	
	//LED for ON/OFF
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	PORTB->PCR[18] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= (1<<18);
	GPIOB->PSOR = (1<<18);
}


void PORTA_IRQHandler(void){
	if(!(GPIOA->PDIR & 0x1000)){ 						//A12 pressed: next waveform
		while(!(GPIOA->PDIR & 0x1000)){}				//stay here until released (debouncing)
		switch(current){
		case 0:
			current = 0;
			break;
		case 1:
			current++;
			break;
		case 2:
			current++;
			break;
		case 3:
			current++;
			break;
		case 4:
			current++;
			PORTE->PCR[30] |= PORT_PCR_MUX(3);
			TPM0->SC = 0;
			TPM0->CONTROLS[3].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;  	//pwm mode
			TPM0->SC |= TPM_SC_CMOD(1); //Start TPM0
			break;
		case 5:
			PORTE->PCR[30] = 0;
			//ADC0->SC3 = 0; 							//no samplinggg
			current++;
			break;
		case 6:
			current = 1;
			break;
		default:
			current = 0;
		}
		PORTA->PCR[12] |= PORT_PCR_ISF_MASK;									//clear interrupt flag
	}
	else if (!(GPIOA->PDIR & 0x20)){ 				//A5 pressed: prev wave
		while(!(GPIOA->PDIR & 0x20)){}
		switch(current){
		case 0:
			current = 0;
			break;
		case 1:
			//ADC0->SC3 = 0; 							//no samplinggg
			current = 6;
			break;
		case 2:
			current--;
			break;
		case 3:
			current--;
			break;
		case 4:
			current--;
			break;
		case 5:
			current--;
			PORTE->PCR[30] = 0;
			break;
		case 6:
			current--;
			PORTE->PCR[30] |= PORT_PCR_MUX(3);
			TPM0->SC = 0;
			TPM0->CONTROLS[3].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;  	//pwm mode	
			TPM0->SC |= TPM_SC_CMOD(1); //Start TPM0
			break;
		default:
			current = 0;
		}
		PORTA->PCR[5] |= PORT_PCR_ISF_MASK;
	}
	else if (!(GPIOA->PDIR & 0x20000)){					//A17 pressed: on/off
		while(!(GPIOA->PDIR & 0x20000)){}
		if(current == 0){
			current = 1;
			GPIOB->PCOR |= (1<<18);						//LED on
		}
		else{
			current = 0;
			GPIOB->PSOR |= (1<<18);						//LED off
		}
		
		PORTA->PCR[17] |= PORT_PCR_ISF_MASK;
	}
}
