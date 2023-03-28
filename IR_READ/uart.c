#include "uart.h"

volatile static unsigned char rx_buffer[RX_BUFFER_SIZE] = { 0 };
volatile static unsigned int rx_count = 0;
volatile static unsigned char uart_tx_busy = 1;

ISR(USART_RX_vect) {
	
	volatile static unsigned int rx_write_pos = 0;
	
	rx_buffer[rx_write_pos] = UDR0;
	rx_count++;
	rx_write_pos++;
	if(rx_write_pos >= RX_BUFFER_SIZE) {
		rx_write_pos = 0;
	}
}

ISR(USART_TX_vect) {
	uart_tx_busy = 1;
}

void uart_init(unsigned long baud, unsigned char high_speed) {
	
	unsigned char speed = 16;
	if(high_speed != 0) {
		speed = 8;
		UCSR0A |= 1 << U2X0;
	}
	
	baud = (F_CPU/(speed * baud)) - 1;
	
	UBRR0H = (baud & 0x0F00) >> 8;
	UBRR0L = (baud & 0x00FF);
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
}

void uart_send_byte(unsigned char c) {
	while(uart_tx_busy == 0);
	uart_tx_busy = 0;
	UDR0 = c;
}

void uart_send_array(char *c, unsigned int len) {
	for(unsigned int i = 0; i < len; i++) {
		uart_send_byte(c[i]);
	}
}

void uart_send_string(char *c) {
	unsigned int i = 0;
	do {
		uart_send_byte(c[i]);
		i++;
		
	} while(c[i] != '\0');
	uart_send_byte(c[i]);
}

char uart_read(void) {
	static unsigned int rx_read_pos = 0;
	unsigned char data = 0;
	
	data = rx_buffer[rx_read_pos];
	rx_read_pos++;
	rx_count--;
	if (rx_read_pos >= RX_BUFFER_SIZE) {
		rx_read_pos = 0;
	}
	return data;
}

unsigned int uart_read_count(void) {
	return rx_count;
}
