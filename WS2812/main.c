#include "main.h"

#define delay_ms 0

uint16_t chain = 600;
uint16_t segment = 50;
uint8_t reverse = 1;
double saturation = 1.0;
double brightness = 0.010;
uint16_t offset = 0;
uint8_t palette[3][360];

int main(void)
{
	led_init();
	
	for (uint16_t i = 0; i < chain; i++) led_pixel(1, 1, 1);
	_delay_ms(500);
	for (uint16_t i = 0; i < chain; i++) led_pixel(0, 0, 0);
	
	for (uint16_t i = 0; i < 360; i++) {
		rgb = hsv_rgb(i, saturation, brightness);
		palette[0][i] = rgb.r; palette[1][i] = rgb.g; palette[2][i] = rgb.b;
	}

	while (1)
	{
		if (reverse) {
			for (uint16_t i = 0; i < chain; i++) {
				uint16_t paletteIndex = ((360 / segment) * ((i + offset - 1) % segment));
				led_pixel(palette[0][paletteIndex], palette[1][paletteIndex], palette[2][paletteIndex]);
			}
			offset--;
			if (offset == 0) offset = segment;
		}
		else {
			for (uint16_t i = 0; i < chain; i++) {
				uint16_t paletteIndex = 359 - ((360 / segment) * ((i + offset) % segment));
				led_pixel(palette[0][paletteIndex], palette[1][paletteIndex], palette[2][paletteIndex]);
			}
			offset++;
			if (offset == segment) offset = 0;
		}
		led_reset();
		_delay_ms(delay_ms);
	}
}
