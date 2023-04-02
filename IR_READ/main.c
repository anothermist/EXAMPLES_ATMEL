#include "main.h"

int main(void) {
	
	irr_init();
	uart_init(9600, 0);
	char start[] = "UART OK\r\n";	
	uart_send_string(start);
	
	
	while (1) {
		
		if (IR_HIGH) {
			
			unsigned int irrValueNow = irr_decode();
			
			if (irrValueNow) {
				char code_string[16];
				snprintf(code_string, 16, "CODE: 0x%02X\r\n", irrValueNow);
				uart_send_string(code_string);
			}
		}
	}
}
