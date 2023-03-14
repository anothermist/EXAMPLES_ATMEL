#include "main.h"

uint8_t brightness = 3;
uint8_t saturation = 100;
uint16_t position = 0;

struct cRGB  { uint8_t g; uint8_t r; uint8_t b; };
struct cRGB led[LEDS];

RGB rgb;

int main(void)
{
	led_init();
	
	for (uint16_t i = 0; i < 1000; i++) led_pixel(1, 1, 1);
	led_reset();
	
	while (1)
	{
		rgb = hsv_rgb(position * (360 / (LEDS % 360)) , saturation, brightness);
		
		for (uint16_t i = 0; i < (LEDS - 1); i++) {
			led[(LEDS - 1) - i].r = led[(LEDS - 2) - i].r;
			led[(LEDS - 1) - i].g = led[(LEDS - 2) - i].g;
			led[(LEDS - 1) - i].b = led[(LEDS - 2) - i].b;
		}
		led[0].r = rgb.r;
		led[0].g = rgb.g;
		led[0].b = rgb.b;
		
		for (uint16_t i = 0; i < LEDS; i++) led_pixel(led[i].r, led[i].g, led[i].b);
		led_reset();
		
		position++;
		if (position == LEDS) position = 0;
		_delay_ms(25);
	}
}
