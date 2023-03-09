#include "main.h"

struct cRGB led[40];

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
	
	for (int i = 0; i < 40; i++) {
		struct HSV data = { i*(360/40), 1, 0.02 };
		struct RGB value = HSVToRGB(data);
		led[i].r=value.R; led[i].g=value.G; led[i].b=value.B;
	}
	ws2812_setleds(led, 40);
	
	_delay_ms(2000);

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
