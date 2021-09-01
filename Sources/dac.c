
#include "common.h"
#include "buttons.h"
#include "dac.h"


int off [50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int sine [50] = {1861,2094,2324,2546,2758,2955,3135,3295,3432,3545,3631,3689,3719,3719,3689,3631,3545,3432,3295,3135,2955,2758,2546,2324,2094,1861,1628,1398,1176,964,767,587,427,289,177,91,32,3,3,32,91,177,289,427,587,767,964,1176,1398,1628};
int ramp [50] = {0,83,167,250,334,417,501,585,668,752,835,919,1002,1086,1170,1253,1337,1420,1504,1587,1671,1755,1838,1922,2005,2089,2172,2256,2340,2423,2507,2590,2674,2757,2841,2925,3008,3092,3175,3259,3342,3426,3510,3593,3677,3760,3844,3927,4011,4095};
int square [50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095};
int triangle [50] = {0,170,341,511,682,853,1023,1194,1365,1535,1706,1876,2047,2218,2388,2559,2730,2900,3071,3241,3412,3583,3753,3924,4095,4095,3924,3753,3583,3412,3241,3071,2900,2730,2559,2388,2218,2047,1876,1706,1535,1365,1194,1023,853,682,511,341,170,0};

int sine2 [50];
int sine4 [50];
int sine6 [50];
int sine8 [50];

int ramp2 [50];
int ramp4 [50];
int ramp6 [50];
int ramp8 [50];

int square2 [50];
int square4 [50];
int square6 [50];
int square8 [50];

int triangle2 [50];
int triangle4 [50];
int triangle6 [50];
int triangle8 [50];

int writeValue;

void DAC0_init(void) {
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;   // clock to DAC module
	DAC0->C1 = 0;               //disable the use of buffer
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACTRGSEL_MASK;     //enable DAC and use software trigger
}


void timer_init(void){
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; 	//Enable clock for TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); //Select Clock source of TPM0 to be MCGIRCLK
    MCG->SC = 0;  //Set MCGIR clock divider to be 1 (no prescaler)
	MCG->C2 |= MCG_C2_IRCS_MASK; //Set MCGIRCLK to 4MHz in the MCG module
	MCG->C1 |= MCG_C1_IRCLKEN_MASK; //Enable MCGIRCLK in the MCG module
	TPM0->SC = 0; //Stop timer TPM0
	TPM0->MOD = 40;
	TPM0->SC |= TPM_SC_TOIE_MASK;
	NVIC->ISER |= (1<<17); 	
	TPM0->SC |= TPM_SC_CMOD(1); //Start TPM0
}


void FTM0_IRQHandler(void){
	switch (current){
			case 0:
				DAC0->DAT[0].DATL = off[writeValue] & 0xff;       
				DAC0->DAT[0].DATH = (off[writeValue] >> 8) & 0x0f;
				break;
			case 1: //sine
				switch(amplifier){
				case 0:
					DAC0->DAT[0].DATL = sine2[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((sine2[writeValue]) >> 8) & 0x0f;
					break;
				case 1:
					DAC0->DAT[0].DATL = sine4[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((sine4[writeValue]) >> 8) & 0x0f;
					break;
				case 2:
					DAC0->DAT[0].DATL = sine6[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((sine6[writeValue]) >> 8) & 0x0f;
					break;
				case 3:
					DAC0->DAT[0].DATL = sine8[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((sine8[writeValue]) >> 8) & 0x0f;
					break;
				case 4:
					DAC0->DAT[0].DATL = sine[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((sine[writeValue]) >> 8) & 0x0f;
					break;
				default:
					DAC0->DAT[0].DATL = sine[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((sine[writeValue]) >> 8) & 0x0f;
				}       
				break;
			case 2: //triangle
				switch(amplifier){
				case 0:
					DAC0->DAT[0].DATL = triangle2[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((triangle2[writeValue]) >> 8) & 0x0f;
					break;
				case 1:
					DAC0->DAT[0].DATL = triangle4[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((triangle4[writeValue]) >> 8) & 0x0f;
					break;
				case 2:
					DAC0->DAT[0].DATL = triangle6[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((triangle6[writeValue]) >> 8) & 0x0f;
					break;
				case 3:
					DAC0->DAT[0].DATL = triangle8[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((triangle8[writeValue]) >> 8) & 0x0f;
					break;
				case 4:
					DAC0->DAT[0].DATL = triangle[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((triangle[writeValue]) >> 8) & 0x0f;
					break;
				default:
					DAC0->DAT[0].DATL = triangle[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((triangle[writeValue]) >> 8) & 0x0f;
				}  
				break;
			case 3: //sawtooth or ramp
				switch(amplifier){
				case 0:
					DAC0->DAT[0].DATL = ramp2[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((ramp2[writeValue]) >> 8) & 0x0f;
					break;
				case 1:
					DAC0->DAT[0].DATL = ramp4[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((ramp4[writeValue]) >> 8) & 0x0f;
					break;
				case 2:
					DAC0->DAT[0].DATL = ramp6[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((ramp6[writeValue]) >> 8) & 0x0f;
					break;
				case 3:
					DAC0->DAT[0].DATL = ramp8[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((ramp8[writeValue]) >> 8) & 0x0f;
					break;
				case 4:
					DAC0->DAT[0].DATL = ramp[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((ramp[writeValue]) >> 8) & 0x0f;
					break;
				default:
					DAC0->DAT[0].DATL = ramp[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((ramp[writeValue]) >> 8) & 0x0f;
				}  
				break;
			case 4: //square
				switch(amplifier){
				case 0:
					DAC0->DAT[0].DATL = square2[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((square2[writeValue]) >> 8) & 0x0f;
					break;
				case 1:
					DAC0->DAT[0].DATL = square4[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((square4[writeValue]) >> 8) & 0x0f;
					break;
				case 2:
					DAC0->DAT[0].DATL = square6[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((square6[writeValue]) >> 8) & 0x0f;
					break;
				case 3:
					DAC0->DAT[0].DATL = square8[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((square8[writeValue]) >> 8) & 0x0f;
					break;
				case 4:
					DAC0->DAT[0].DATL = square[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((square[writeValue]) >> 8) & 0x0f;
					break;
				default:
					DAC0->DAT[0].DATL = square[writeValue] & 0xff;       
					DAC0->DAT[0].DATH = ((square[writeValue]) >> 8) & 0x0f;
				}      
				break;
			default:
				DAC0->DAT[0].DATL = off[writeValue] & 0xff;  
				DAC0->DAT[0].DATH = (off[writeValue] >> 8) & 0x0f;
			}
	if(writeValue == 49){
		writeValue = 0;
	}
	else{
		writeValue++;
	}
	TPM0->SC |= TPM_SC_TOF_MASK;  //clear TOF 
}


void init_arrays(void){
	int x;
	for(x=0;x<50;x++){
		sine2[x] = sine[x]*1/5;
		sine4[x] = sine[x]*2/5;
		sine6[x] = sine[x]*3/5;
		sine8[x] = sine[x]*4/5;
		ramp2[x] = ramp[x]*1/5;
		ramp4[x] = ramp[x]*2/5;
		ramp6[x] = ramp[x]*3/5;
		ramp8[x] = ramp[x]*4/5;
		square2[x] = square[x]*1/5;
		square4[x] = square[x]*2/5;
		square6[x] = square[x]*3/5;
		square8[x] = square[x]*4/5;
		triangle2[x] = triangle[x]*1/5;
		triangle4[x] = triangle[x]*2/5;
		triangle6[x] = triangle[x]*3/5;
		triangle8[x] = triangle[x]*4/5;
	}
}
