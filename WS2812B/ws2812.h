#ifndef WS2812_H_
#define WS2812_H_

#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_DATA_PIN  0
#define LED_DATA_PORT C
#define LED_RESETTIME  50 // WS2812 and clones only need 50 µs, WS2813 needs 300 µs reset time
#define INTERRUPT_DISABLE // Normally ws2812_sendarray_mask() runs under disabled-interrupt condition, undefine if you want to accept interrupts in that function.

#define CONCAT(a, b)            a ## b
#define CONCAT_EXP(a, b)   CONCAT(a, b)
#define WS2812_PORTREG  CONCAT_EXP(PORT, LED_DATA_PORT)
#define WS2812_DDRREG   CONCAT_EXP(DDR,  LED_DATA_PORT)

void ws2812_send(uint8_t *data);

struct cRGB  { uint8_t g; uint8_t r; uint8_t b; }; // WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
struct cRGBW { uint8_t g; uint8_t r; uint8_t b; uint8_t w;}; // SK6812RGBW

void ws2812_setleds     (struct cRGB  *ledarray, uint16_t number_of_leds);
void ws2812_setleds_pin (struct cRGB  *ledarray, uint16_t number_of_leds, uint8_t pinmask);
void ws2812_setleds_rgbw(struct cRGBW *ledarray, uint16_t number_of_leds);

void ws2812_sendarray     (uint8_t *array, uint16_t length);
void ws2812_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask);

#endif /* WS2812_H_ */
