
#include "common.h"
#include "buttons.h"
#include "uart.h"
#include "dac.h"
#include "adc.h"

/* 
 * Initializes UART0 to communicate uC and computer via Serial connection
 */
void UART0_init(void) {
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; 					//enable clock to UART0
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); 					//Select FLL as the clock for UART0
	
	UART0->C2 = 0; 											//Disable UART0 to configure
	
	//to generate 115200 baud
	UART0->BDH = 0;
	UART0->BDL = 13; 										//Set SBR to 13
	UART0->C4 = 13;  										//Set OSR to 13
	
	UART0->C1 = 0; 											//8 bit data, no parity, 1 stop bit
	//UART0->C2 |= UART0_C2_RE_MASK | UART0_C2_RIE_MASK; 		//Receive and receive interrupt enable
	UART0->C2 |= UART0_C2_RE_MASK;
	NVIC->ISER |= (1<<12); 									//interruption
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 					//Enable clock to PORTA
	PORTA->PCR[1] = PORT_PCR_MUX(2);  						//Configure PTA1 as UART0_Rx pin 
	
	UART0->C2 |= UART0_C2_TE_MASK;     						//Transmit enable
	PORTA->PCR[2] = PORT_PCR_MUX(2); 						//Configure PTA2 as UART0_Tx pin 
}


void UART_status(void){
	UART_string("====================",20);
	UART_string("\n\r",2);
	switch (current){
	case 1:
		UART_string("Mode: Normal\n\r",14);
		UART_string("Waveform: Sine\n\r",16);
		UART_string("Frequency: ",11);
		frequency_string(80000/TPM0->MOD);
		UART_string("\n\r",2);
		UART_string("Max voltage: ",13);
		switch(amplifier){
		case 0:
			UART_string("0.6V",4);
			break;
		case 1:
			UART_string("1.2V",4);
			break;
		case 2:
			UART_string("1.8V",4);
			break;
		case 3:
			UART_string("2.4V",4);
			break;
		case 4:
			UART_string("3V",2);
			break;
		default:
			UART_string("3V",2);
		}
		UART_string("\n\r",2);
		UART_string("Output: ON\n\r",12);
		break;
	case 2:
		UART_string("Mode: Normal\n\r",14);
		UART_string("Waveform: Triangle\n\r",20);
		UART_string("Frequency: ",11);
		frequency_string(80000/TPM0->MOD);
		UART_string("\n\r",2);
		UART_string("Max voltage: ",13);
		switch(amplifier){
		case 0:
			UART_string("0.66V",5);
			break;
		case 1:
			UART_string("1.32V",5);
			break;
		case 2:
			UART_string("1.98V",5);
			break;
		case 3:
			UART_string("2.664",5);
			break;
		case 4:
			UART_string("3.3V",4);
			break;
		default:
			UART_string("3.3V",4);
		}
		UART_string("\n\r",2);
		UART_string("Output: ON\n\r",12);
		break;
	case 3:
		UART_string("Mode: Normal\n\r",14);
		UART_string("Waveform: Sawtooth\n\r",20);
		UART_string("Frequency: ",11);
		frequency_string(80000/TPM0->MOD);
		UART_string("\n\r",2);
		UART_string("Max voltage: ",13);
		switch(amplifier){
		case 0:
			UART_string("0.66V",5);
			break;
		case 1:
			UART_string("1.32V",5);
			break;
		case 2:
			UART_string("1.98V",5);
			break;
		case 3:
			UART_string("2.664",5);
			break;
		case 4:
			UART_string("3.3V",4);
			break;
		default:
			UART_string("3.3V",4);
		}
		UART_string("\n\r",2);
		UART_string("Output: ON\n\r",12);
		break;
	case 4:
		UART_string("Mode: Normal\n\r",14);
		UART_string("Waveform: Square\n\r",18);
		UART_string("Frequency: ",11);
		frequency_string(80000/TPM0->MOD);
		UART_string("\n\r",2);
		UART_string("Max voltage: ",13);
		switch(amplifier){
		case 0:
			UART_string("0.66V",5);
			break;
		case 1:
			UART_string("1.32V",5);
			break;
		case 2:
			UART_string("1.98V",5);
			break;
		case 3:
			UART_string("2.664",5);
			break;
		case 4:
			UART_string("3.3V",4);
			break;
		default:
			UART_string("3.3V",4);
		}
		UART_string("\n\r",2);
		UART_string("Output: ON\n\r",12);
		break;
	case 5:
		UART_string("Mode: Normal\n\r",14);
		UART_string("Waveform: PWM\n\r",15);
		UART_string("Frequency: ",11);
		frequency_string(80000/TPM0->MOD);
		UART_string("\n\r",2);
		UART_string("Duty cycle: ",12);
		switch(amplifier){
				case 0:
					UART_string("20%",3);
					break;
				case 1:
					UART_string("40%",3);
					break;
				case 2:
					UART_string("60%",3);
					break;
				case 3:
					UART_string("80%",3);
					break;
				case 4:
					UART_string("100%",4);
					break;
				default:
					UART_string("100%",4);
				}
		UART_string("\n\r",2);
		UART_string("Output: ON\n\r",12);
		break;
	case 6:
		UART_string("Mode: Bypass\n\r",14);
		UART_string("Instant voltage: ",17);
		UART_string("\n\r",2);
		UART_string("Upper saturated: ",17);
		UART_string("\n\r",2);
		UART_string("Lower saturated: ",17);
		UART_string("\n\r",2);
		UART_string("Gain: ",6);
		if(gain == 1){
			UART_string("0.5",3);
		}
		else{
			frequency_string(gain/2);
		}
		UART_string("\n\r",2);
		UART_string("Max gain: ",10);
		UART_string("\n\r",2);
		UART_string("Output: ON\n\r",12);
		break;
	default:
		UART_string("OFF\n\r",5);
	}
}


void UART_string(char string[], int size){
	int i;
	for (i=0;i<size;i++){
		UART0->D = string[i];
		while(!(UART0->S1 & UART0_S1_TC_MASK)){}
	}
}


void frequency_string(int k){
	int digits = 0;
	int copy = k;

		while(copy!=0){
			copy/= 10;
			digits++;
		}
		
		int digitsArray[digits];
		int w;
		for(w=0;w<digits;w++){
			digitsArray[w] = k%10;
			k = k/10;
		}
		
		int z;
		for(z=digits-1;z>-1;z--){
			switch(digitsArray[z]){
			case 1:
				UART_string("1",1);
				break;
			case 2:
				UART_string("2",1);
				break;
			case 3:
				UART_string("3",1);
				break;
			case 4:
				UART_string("4",1);
				break;
			case 5:
				UART_string("5",1);
				break;
			case 6:
				UART_string("6",1);
				break;
			case 7:
				UART_string("7",1);
				break;
			case 8:
				UART_string("8",1);
				break;
			case 9:
				UART_string("9",1);
				break;
			case 0:
				UART_string("0",1);
				break;
			}
		}
}

