#include "main.h"

#define length 300
#define saturation 1.00  // 0.00 ~ 1.00
#define brightness 0.05  // 0.00 ~ 1.00

struct cRGB led[length];
struct RGB { uint8_t R; uint8_t G; uint8_t B; };
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
	
	for (uint16_t i=0; i<length; i++) {
		led[i].r=1; led[i].g=1; led[i].b=1;
	}
	ws2812_setleds(led, length);
	_delay_ms(1000);
	
	uint16_t move_delay = 100;
	//int8_t direction = 1;
	uint16_t position = 0;
	
	for (uint16_t i = 0; i < length; i++) {
		struct HSV data = { i*(360/length), saturation, brightness };
		struct RGB value = HSVToRGB(data);
		led[i].r=value.R; led[i].g=value.G; led[i].b=value.B;
	}
	
	while(1) {
		
		struct HSV data = { position*(360/(length)), saturation, brightness };
		struct RGB value = HSVToRGB(data);

		uint8_t tempR = value.R; // led[0].r;
		uint8_t tempG = value.G; // led[0].g;
		uint8_t tempB = value.B; // led[0].b;
		
		for (uint16_t i = 0; i < (length-1); i++) {
		led[i].r = led[i+1].r;
		led[i].g = led[i+1].g;
		led[i].b = led[i+1].b;
		}
		led[length-1].r = tempR;
		led[length-1].g = tempG;
		led[length-1].b = tempB;
		
		ws2812_setleds(led, length);
		position++;
		if (position == length) position = 0;
		_delay_ms(move_delay);
		
		
		//for (uint8_t i=0; i<position; i++)
		//ws2812_send((uint8_t *)&led[1]);
		//
		//for (uint8_t i=0; i<(length-position); i++)
		//ws2812_send((uint8_t *)&led[26]);
		//
		//position+=direction;
		//if ((position==40)||(position==0)) direction=-direction;
		//_delay_ms(move_delay);
	}
}
