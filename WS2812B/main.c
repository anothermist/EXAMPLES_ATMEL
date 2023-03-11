#include "main.h"

#define length 40
struct cRGB led[length];

struct RGB { unsigned char R; unsigned char G; unsigned char B; };
struct HSV { double H; double S; double V; };

struct RGB HSVToRGB(struct HSV hsv) {
	double r = 0, g = 0, b = 0;

	if (hsv.S == 0) {
		r = hsv.V;
		g = hsv.V;
		b = hsv.V;
	}
	else {
		int i;
		double f, p, q, t;

		if (hsv.H == 360)
		hsv.H = 0;
		else
		hsv.H = hsv.H / 60;

		i = (int)trunc(hsv.H);
		f = hsv.H - i;

		p = hsv.V * (1.0 - hsv.S);
		q = hsv.V * (1.0 - (hsv.S * f));
		t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

		switch (i) {
			case 0:
			r = hsv.V;
			g = t;
			b = p;
			break;

			case 1:
			r = q;
			g = hsv.V;
			b = p;
			break;

			case 2:
			r = p;
			g = hsv.V;
			b = t;
			break;

			case 3:
			r = p;
			g = q;
			b = hsv.V;
			break;

			case 4:
			r = t;
			g = p;
			b = hsv.V;
			break;

			default:
			r = hsv.V;
			g = p;
			b = q;
			break;
		}

	}

	struct RGB rgb;
	rgb.R = r * 255;
	rgb.G = g * 255;
	rgb.B = b * 255;

	return rgb;
}

int main(void) {
	
	for (int i=0; i<length; i++) {
		led[i].r=1; led[i].g=1; led[i].b=1;
	}
	ws2812_setleds(led, length);
	_delay_ms(1000);
	
	//uint8_t pos = 0;
	//uint8_t direction = 1;
	
	for (int i = 0; i < length; i++) {
		struct HSV data = { i*(360/length), 1, 0.02 };
		struct RGB value = HSVToRGB(data);
		led[i].r=value.R; led[i].g=value.G; led[i].b=value.B;
	}
	ws2812_setleds(led, length);
	
	_delay_ms(1000);
	
	
	while(1) {
	uint8_t tempR = led[0].r;
	uint8_t tempG = led[0].g;
	uint8_t tempB = led[0].b;
	
	for (uint8_t i = 0; i < (length - 1); i++) {
	led[i].r = led[i+1].r;
	led[i].g = led[i+1].g;
	led[i].b = led[i+1].b;
	}
	led[length-1].r = tempR;
	led[length-1].g = tempG;
	led[length-1].b = tempB;
	
	ws2812_setleds(led, length);
	_delay_ms(100);
	
	
	//for (uint8_t i=0; i<pos; i++)
	//ws2812_send((uint8_t *)&led[1]);
	//
	//_delay_ms(100);
	//
	//for (uint8_t i=0; i<(length-pos); i++)
	//ws2812_send((uint8_t *)&led[26]);
	//
	//pos+=direction;
	//if ((pos==40)||(pos==0)) direction=-direction;
	
	}
}
