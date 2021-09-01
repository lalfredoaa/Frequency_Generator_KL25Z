
#ifndef UART_H_
#define UART_H_

/* 
 * Initializes UART0 to communicate uC and computer via Serial connection
 */
void UART0_init(void);


void UART_status(void);

void UART_string(char string[], int size);

void frequency_string (int k);

#endif /* UART_H_ */
