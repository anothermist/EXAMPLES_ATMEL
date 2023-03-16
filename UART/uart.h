#ifndef UART_H_
#define UART_H_

#include "main.h"

#define RX_BUFFER_SIZE 128

void uart_init(uint32_t baud, uint8_t high_speed);
void uart_send_byte(uint8_t c);
void uart_send_array(uint8_t *c, uint16_t len);
void uart_send_string(const uint8_t *c);
uint8_t uart_read(void);
uint16_t uart_read_count(void);

#endif /* UART_H_ */
