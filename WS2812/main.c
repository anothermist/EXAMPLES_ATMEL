#include "main.h"

#define delay_ms 5

unsigned int chain = 600;
unsigned int segment = 50;
unsigned char reverse = 1;
double saturation = 1.0;
double brightness = 0.1;
unsigned int offset = 0;
unsigned char palette[3][360];

int main(void)
{
	led_init();
	
	for (unsigned int i = 0; i < chain; i++) led_pixel(1, 1, 1);
	_delay_ms(500);
	for (unsigned int i = 0; i < chain; i++) led_pixel(0, 0, 0);
	
	for (unsigned int i = 0; i < 360; i++) {
		rgb = hsv_rgb(i, saturation, brightness);
		palette[0][i] = rgb.r; palette[1][i] = rgb.g; palette[2][i] = rgb.b;
	}

	while (1)
	{
		if (reverse) {
			for (unsigned int i = 0; i < chain; i++) {
				unsigned int paletteIndex = ((360 / segment) * ((i + offset - 1) % segment));
				led_pixel(palette[0][paletteIndex], palette[1][paletteIndex], palette[2][paletteIndex]);
			}
			offset--;
			if (offset == 0) offset = segment;
		}
		else {
			for (unsigned int i = 0; i < chain; i++) {
				unsigned int paletteIndex = 359 - ((360 / segment) * ((i + offset) % segment));
				led_pixel(palette[0][paletteIndex], palette[1][paletteIndex], palette[2][paletteIndex]);
			}
			offset++;
			if (offset == segment) offset = 0;
		}
		led_reset();
		_delay_ms(delay_ms);
	}
}
