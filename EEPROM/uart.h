#ifndef UART_H_
#define UART_H_

#include "main.h"

#define RX_BUFFER_SIZE 128

void uart_init(unsigned long baud, unsigned char high_speed);
void uart_send_byte(unsigned char c);
void uart_send_array(char *c, unsigned int len);
void uart_send_string(char *c);
char uart_read(void);
unsigned int uart_read_count(void);

#endif /* UART_H_ */
