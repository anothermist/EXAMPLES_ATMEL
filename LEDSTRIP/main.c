#include "main.h"

#define length 600
#define saturation 1.000  // 0.00 ~ 1.00
#define brightness 0.025  // 0.00 ~ 1.00

#define rainbow_leds 300  // 0.00 ~ 1.00

struct cRGB led[length];

struct RGB { uint8_t R; uint8_t G; uint8_t B; };
struct HSV { double H; double S; double V; };

struct RGB HSVToRGB(struct HSV hsv) {
	double r = 0, g = 0, b = 0;

	if (hsv.S == 0) { r = hsv.V; g = hsv.V; b = hsv.V; }
	else {
		uint16_t i;
		double f, p, q, t;

		if (hsv.H == 360) hsv.H = 0;
		else hsv.H = hsv.H / 60;

		i = (uint16_t)trunc(hsv.H);
		f = hsv.H - i;

		p = hsv.V * (1.0 - hsv.S);
		q = hsv.V * (1.0 - (hsv.S * f));
		t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

		switch (i) {
			case 0:  r = hsv.V; g = t;     b = p;     break;
			case 1:  r = q;     g = hsv.V; b = p;     break;
			case 2:  r = p;     g = hsv.V; b = t;     break;
			case 3:  r = p;     g = q;     b = hsv.V; break;
			case 4:  r = t;     g = p;     b = hsv.V; break;
			default: r = hsv.V; g = p;     b = q;     break;
		}

	}
	struct RGB rgb;
	rgb.R = r * 255; rgb.G = g * 255; rgb.B = b * 255;
	return rgb;
}

int main(void) {
	
	for (uint16_t i=0; i < length; i++) {
		led[i].r=1; led[i].g=1; led[i].b=1;
	}
	ledstrip_setleds(led, length);
	_delay_ms(1000);
	
	uint16_t move_delay = 25;
	int8_t direction = 1;
	uint16_t position = 0;
	
	//for (uint16_t i = 0; i < length; i++) {
		//struct HSV data = { i * (360 / (length % 360 )), saturation, brightness };
		//struct RGB value = HSVToRGB(data);
		//led[i].r = value.R;
		//led[i].g = value.G;
		//led[i].b = value.B;
	//}
	
	while(1) {
		
		struct HSV data = { position * (360 / (rainbow_leds % 360 )), saturation, brightness };
		struct RGB value = HSVToRGB(data);
		
		for (uint16_t i = 0; i < (rainbow_leds - 1); i++) {
			if (direction) {		
				led[(rainbow_leds - 1) - i].r = led[(rainbow_leds - 2) - i].r;
				led[(rainbow_leds - 1) - i].g = led[(rainbow_leds - 2) - i].g;
				led[(rainbow_leds - 1) - i].b = led[(rainbow_leds - 2) - i].b;
			}
			else {				
				led[i].r = led[i + 1].r;
				led[i].g = led[i + 1].g;
				led[i].b = led[i + 1].b;
			}
		}
		if (direction) {
			led[0].r = value.R;
			led[0].g = value.G;
			led[0].b = value.B;
			} else {
			led[rainbow_leds - 1].r = value.R;
			led[rainbow_leds - 1].g = value.G;
			led[rainbow_leds - 1].b = value.B;
		}
		ledstrip_setleds(led, rainbow_leds);
		position++;
		if (position == rainbow_leds) position = 0;
		_delay_ms(move_delay);
		
		//led[0].r=8; led[0].g=0; led[0].b=0;
		//led[1].r=0; led[1].g=0; led[1].b=8;
		//
		//for (uint16_t i = 0; i < position; i++)
		//ledstrip_send((uint8_t *)&led[0]);
		//
		//for (uint16_t i = 0; i < (length - position); i++)
		//ledstrip_send((uint8_t *)&led[1]);
		//
		//position+=direction;
		//if ((position == length)||(position == 0)) direction =- direction;
		//_delay_ms(move_delay);	
		
	}
}
