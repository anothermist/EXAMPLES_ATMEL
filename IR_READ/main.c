#include "main.h"

int main(void) {

	DDRD |= 0xF0; //0b11110000
	uart_init(9600, 0);
	sei();
	
	char start[] = "UART OK\r\n";
	
	uart_send_string(start);
	DDRD = 0xFF; PORTD = 0x00;
	
	irrTimerInit();
	
	while (1) {
		
		if (IR_HIGH) {
			
			unsigned int irrValueNow = irrDecode();
			
			if (irrValueNow) {
				char code_string[16];
				snprintf(code_string, 16, "CODE: 0x%02X\r\n", irrValueNow);
				uart_send_string(code_string);
			}
		}
	}
}
