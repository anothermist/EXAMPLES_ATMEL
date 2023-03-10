#ifndef WS2812_H_
#define WS2812_H_

#include "main.h"
#include <math.h>

#define LEDS 300
#define LED_PORT  PORTC
#define LED_DDR   DDRC
#define LED_PIN   0 

#define T1H 560 // 560 - 700 - 900   // Width of a 1 bit in ns
#define T1L 130 // 130 - 600 - 600   // Width of a 1 bit in ns
#define T0H 130 // 130 - 350 - 400   // Width of a 0 bit in ns
#define T0L 250 // 250 - 800 - 900   // Width of a 0 bit in ns
#define RES 50  // WS2812 need 50 us, WS2813 needs 300 us reset time

typedef struct RGB { uint8_t r; uint8_t g; uint8_t b; } RGB;

void led_init();
void led_reset();
void led_pixel(uint8_t r, uint8_t g, uint8_t b);
void led_color(uint8_t r, uint8_t g, uint8_t b);
RGB hsv_rgb (float H, float S, float V);

#endif /* WS2812_H_ */