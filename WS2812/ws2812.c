#include "ws2812.h"

#define NS_PER_SEC (1000000000L)
#define CYCLES_PER_SEC (F_CPU)
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

void led_init() {
	bitSet(LED_DDR, LED_PIN);
}

void led_reset() {
	_delay_us(RES);
}

inline void sendBit(bool bitVal) {
	if (bitVal) {                                   // 0 bit
		asm volatile (
		"sbi %[port], %[bit] \n\t"                  // Set the output bit
		".rept %[onCycles] \n\t"                    // Execute NOPs to delay exactly the specified number of cycles
		"nop \n\t"
		".endr \n\t"
		"cbi %[port], %[bit] \n\t"                  // Clear the output bit
		".rept %[offCycles] \n\t"                   // Execute NOPs to delay exactly the specified number of cycles
		"nop \n\t"
		".endr \n\t"
		::
		[port]		"I" (_SFR_IO_ADDR(LED_PORT)),
		[bit]		"I" (LED_PIN),
		[onCycles]	"I" (NS_TO_CYCLES(T1H) - 2),    // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work
		[offCycles] "I" (NS_TO_CYCLES(T1L) - 2)     // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness
		);
		} else {                                    // 1 bit
		asm volatile (
		"sbi %[port], %[bit] \n\t"                  // Set the output bit
		".rept %[onCycles] \n\t"                    // Now timing actually matters. The 0-bit must be long enough to be detected but not too long or it will be a 1-bit
		"nop \n\t"                                  // Execute NOPs to delay exactly the specified number of cycles
		".endr \n\t"
		"cbi %[port], %[bit] \n\t"                  // Clear the output bit
		".rept %[offCycles] \n\t"                   // Execute NOPs to delay exactly the specified number of cycles
		"nop \n\t"
		".endr \n\t"
		::
		[port]		"I" (_SFR_IO_ADDR(LED_PORT)),
		[bit]		"I" (LED_PIN),
		[onCycles]	"I" (NS_TO_CYCLES(T0H) - 2),
		[offCycles]	"I" (NS_TO_CYCLES(T0L) - 2)
		);
	}
}

inline void sendByte(uint8_t byte) {
	for(uint8_t bit = 0 ; bit < 8 ; bit++) {
		sendBit(bitRead(byte, 7));
		byte <<= 1;
	}
}

void led_pixel(uint8_t r, uint8_t g, uint8_t b)  {
	sendByte(g);
	sendByte(r);
	sendByte(b);
}

void led_color(uint8_t r, uint8_t g, uint8_t b) {
	cli();
	for(uint16_t i = 0; i < LEDS; i++) {
		led_pixel(r, g, b);
	}
	sei();
	led_reset();
}

RGB hsv_rgb (float H, float S, float V) {
	float r = 0, g = 0, b = 0;
	
	float h = H / 360;
	float s = S / 100;
	float v = V / 100;
	
	int i = floor(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);
	
	switch (i % 6) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}
	
	RGB rgb;
	rgb.r = r * 255;
	rgb.g = g * 255;
	rgb.b = b * 255;
	
	return rgb;
}
