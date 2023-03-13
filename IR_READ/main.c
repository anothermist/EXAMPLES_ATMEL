#include "main.h"

int main(void) {
	DDRD = 0xFF; PORTD = 0x00;
	irrTimerInit();
	uartInit();
	
	while (1) {
			
		if (IR_HIGH) {
			
			uint16_t irrValueNow = irrDecode();
			
			if (irrValueNow) {
				uartTransmitHex(0, irrValueNow);
				uartNewLine();
				
				char code_string[11];
				snprintf(code_string, 11, "CODE: 0x%02X ", irrValueNow);
			}
		}
	}
}
