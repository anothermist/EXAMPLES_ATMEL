#include "main.h"

struct cRGB led[40];

int main(void) {

	uint8_t pos=0;
	uint8_t direction=1;
	uint8_t i;
	
	for (int i=0; i<40; i++) {
		led[i].r=1; led[i].g=1; led[i].b=1;
	}
	ws2812_setleds(led, 40);
	_delay_ms(500);
	
	led[0].r=0; led[0].g=0; led[0].b=0;
	led[1].r=1; led[1].g=0; led[1].b=0;
	led[2].r=0; led[2].g=1; led[2].b=0;
	led[3].r=0; led[3].g=0; led[3].b=1;
	
	
	for (i=0; i<40; i++) ws2812_send((uint8_t *)&led[0]);
	_delay_ms(500);
	for (i=0; i<40; i++) ws2812_send((uint8_t *)&led[2]);
	_delay_ms(500);
	
	
	while(1) {

		for (i=0; i<pos; i++)
		ws2812_send((uint8_t *)&led[1]);
		
		_delay_ms(500);
		
		for (i=0; i<(40-pos); i++)
		ws2812_send((uint8_t *)&led[3]);
		
		pos+=direction;
		if ((pos==40)||(pos==0)) direction=-direction;
	}
}
