#include "main.h"

int main(void)
{
	char start[] = "UART OK\r\n";
	char data = 'A';
	unsigned char counter = 0x10; //0b00010000
	
	DDRD |= 0xF0; //0b11110000
	uart_init(9600, 0);
	uart_send_string(start);
	
	while (1) {
		
		if (uart_read_count() > 0) {
			data = uart_read();
			uart_send_byte(data);

			PORTD &= 0x0F; //0b00001111
			PORTD |= counter;
			
			if (counter >= 0x80) counter = 0x10;
			else counter *= 2;
		}

	}
}
