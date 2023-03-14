#ifndef WS2812_H_
#define WS2812_H_

#include "main.h"

#define LEDS 40

#define LED_PORT  PORTC
#define LED_DDR   DDRC
#define LED_PIN   0 

#define T1H 900 // 560 - 700 - 900   // Width of a 1 bit in ns
#define T1L 600 // 130 - 600 - 600   // Width of a 1 bit in ns
#define T0H 400 // 130 - 350 - 400   // Width of a 0 bit in ns
#define T0L 900 // 250 - 800 - 900   // Width of a 0 bit in ns
#define RES 50  // WS2812 need 50 us, WS2813 needs 300 us reset time

void led_init();
void led_reset();
void led_pixel(uint8_t r, uint8_t g, uint8_t b);
void led_color(uint8_t r, uint8_t g, uint8_t b);

#endif /* WS2812_H_ */