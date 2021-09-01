
#include "common.h"
#include "adc.h"
#include "buttons.h"
#include "dac.h"

int channel = 0;

//int gain;

int samples [50];
int currentSample = 0;
int x;


void ADC0_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;      //clock to PORTE
	PORTE->PCR[20] = 0;         			 //PTE20 analog input
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;   	 //clock to ADC0
	ADC0->SC2 &= (~ADC_SC2_ADTRG_MASK);      //software trigger 
	//clock div by 8, long sample time, single ended 12 bit, bus clock/2
	ADC0->CFG1 |= ADC_CFG1_ADIV(8) | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(1) | ADC_CFG1_ADICLK(1);
	
	ADC0->SC3 |= ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(1); //average 32 samples
	
	ADC0->SC1[0] = 0; //start and use channel 0
	ADC0->SC1[0] |= ADC_SC1_AIEN_MASK; //interrupt enable
	NVIC->ISER |= (1<<15);
		
	PORTE->PCR[22] = 0;         			//PTE22 analog input
	PORTE->PCR[21] = 0;
	
	
	//LEDs for saturation
	PORTB->PCR[1] |= PORT_PCR_MUX(1); //upper saturation led
	PORTB->PCR[2] |= PORT_PCR_MUX(1); //lower saturation led
	GPIOB->PDDR |= (1<<1);
	GPIOB->PDDR |= (1<<2);
	GPIOB->PCOR |= (1<<1);
	GPIOB->PCOR |= (1<<2);
}


void ADC0_IRQHandler(void){
	int value;
	value = ADC0->R[0];
	if(channel == 0){
		TPM0->SC = 0; //Stop timer TPM0
		//TPM0->MOD = 3*value+40; for 8 bit
		if((current != 5)&&((current != 6))){ //not pwm nor bypass mode
			TPM0->SC |= TPM_SC_TOIE_MASK;
			TPM0->MOD = 185*value/1000+40;
			TPM0->SC |= TPM_SC_CMOD(1); //Start TPM0
			channel = 1;
			ADC0->SC1[0] |= ADC_SC1_ADCH(3); 		//start and use channel 1 (adc 3)
		}
		else if (current == 5){ //pwm
			TPM0->MOD = (185*value/1000+40)*50;
			switch(amplifier){
			case 0:
				TPM0->CONTROLS[3].CnV = 50*(185*value/1000+40)/5;//pulse width
				break;
			case 1:
				TPM0->CONTROLS[3].CnV = 50*(185*value/1000+40)/5*2;//pulse width
				break;
			case 2:
				TPM0->CONTROLS[3].CnV = 50*(185*value/1000+40)/5*3;//pulse width
				break;
			case 3:
				TPM0->CONTROLS[3].CnV = 50*(185*value/1000+40)/5*4;//pulse width
				break;
			case 4:
				TPM0->CONTROLS[3].CnV = 50*(185*value/1000+40);//pulse width
				break;
			default:
				TPM0->CONTROLS[3].CnV = 50*(185*value/1000+40);//pulse width
			}
			TPM0->SC |= TPM_SC_CMOD(1); //Start TPM0
			channel = 1;
			ADC0->SC1[0] |= ADC_SC1_ADCH(3); 		//start and use channel 1 (adc 3)
		}
		else{ //bypass
			if((value<2095)&&(value>2000)){
				//gain = 1
				gain = 2;
			}
			else if (value > 2095){
				//gain <1
				gain = 1;
			}
			else if ((value>1800)&&(value < 2000)){
				//gain = 2
				gain = 4;
			}
			else if ((value>1600)&&(value < 1800)){
				//gain = 3
				gain = 6;
			}
			else if ((value>1400)&&(value < 1600)){
				//gain = 4
				gain = 8;
			}
			else if ((value>1200)&&(value < 1400)){
				//gain = 5
				gain = 10;
			}
			else if ((value>1000)&&(value < 1200)){
				//gain = 6
				gain = 12;
			}
			else if ((value>800)&&(value < 1000)){
				//gain = 7
				gain = 14;
			}
			else if ((value>600)&&(value < 800)){
				//gain = 8
				gain = 16;
			}
			else if ((value>400)&&(value < 600)){
				//gain = 9
				gain = 18;
			}
			else if (value <400){
				//gain = 10
				gain = 20;
			}
			channel = 2;
			ADC0->SC1[0] |= ADC_SC1_ADCH(4);		//start and use channel 2 (adc 4)
		}
	}
	else if (channel == 1){
		amplifier = (4095-value)/819;
		//return to channel 0
		ADC0->SC1[0] = 0; //start and use channel 0
		ADC0->SC1[0] |= ADC_SC1_AIEN_MASK; //interrupt enable
		channel = 0;
	}
	else{
		//channel 2: bypass
		if((value*gain/2)>4094){
			DAC0->DAT[0].DATL =  4095 & 0xff;       
			DAC0->DAT[0].DATH = (4095 >> 8) & 0x0f;		//upper saturation
			GPIOB->PSOR |= (1<<1);
		}
		else if((value*gain/2)<1){
			DAC0->DAT[0].DATL = 0;       
			DAC0->DAT[0].DATH = 0;		//lower saturation
			GPIOB->PSOR |= (1<<2);
		}
		else
		{
			DAC0->DAT[0].DATL =  (value*gain/2) & 0xff;       
			DAC0->DAT[0].DATH = ((value*gain/2) >> 8) & 0x0f;
			GPIOB->PCOR |= (1<<1);
			GPIOB->PCOR |= (1<<2);
		}

		//return to channel 0
		ADC0->SC1[0] = 0; //start and use channel 0
		ADC0->SC1[0] |= ADC_SC1_AIEN_MASK; //interrupt enable
		channel = 0;	
	}
	ADC0->SC1[0] |= ADC_SC1_COCO_MASK; //clear flag
}







