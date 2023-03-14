#include "main.h"

int main(void)
{
	led_init();
	
	for (uint16_t i = 0; i < 40; i++) {
		led_pixel(1, 1, 1);
	}
	
	_delay_ms(500);
	
	for (uint16_t i = 0; i < 40; i++) {
		led_pixel(0, 0, 0);
	}
	
	while (1)
	{

	}
}
