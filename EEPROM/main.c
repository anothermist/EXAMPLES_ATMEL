#include "main.h"

char print_buffer[64] = { 0 };

int main(void) {
	//char start[] = "Program Start \r\n";
	unsigned char run = 0;
	unsigned char err = 0;
	
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	uart_init(9600, 0);

	//uart_send_string(start);
	
	err = EEPROM_read(10, &run);
	
	//memset(print_buffer, 0, sizeof(print_buffer));
	//sprintf(print_buffer,"%d value %d\r\n", __LINE__, run);
	//uart_send_string(print_buffer);
	
	//unsigned int c = run + 1;
	//
	//memset(print_buffer, 0, sizeof(print_buffer));
	//sprintf(print_buffer,"%d value %d\r\n", __LINE__, c);
	//uart_send_string(print_buffer);
	//
	//err = EEPROM_update(10, c);
//
	//PORTD &= 0x0F;
	//PORTB &= 0xF0;
	//PORTD |= ((run & 0x0F) << 4);
	//PORTB |= ((run & 0xF0) >> 4);
	
	
	sprintf(print_buffer,"value %d\r\n", run);
	uart_send_string(print_buffer);
	
	unsigned char test = 5;
	EEPROM_write(100, test);
	
	while (1) {

	}
}
