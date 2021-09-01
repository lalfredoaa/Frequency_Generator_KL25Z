
#ifndef DAC_H_
#define DAC_H_

void DAC0_init(void);
void timer_init(void);
void FTM0_IRQHandler(void);
void init_arrays(void);

int amplifier;


#endif /* DAC_H_ */
