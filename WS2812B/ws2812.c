#include "ws2812.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void inline ws2812_send(uint8_t *data) {
	ws2812_sendarray_mask(data, 3, _BV(LED_DATA_PIN));
}

void inline ws2812_setleds(struct cRGB *ledarray, uint16_t leds) {
   ws2812_setleds_pin(ledarray, leds, _BV(LED_DATA_PIN));
}

void inline ws2812_setleds_pin(struct cRGB *ledarray, uint16_t leds, uint8_t pinmask) {
  ws2812_sendarray_mask((uint8_t*)ledarray, leds+leds+leds, pinmask);
  _delay_us(LED_RESETTIME);
}

void inline ws2812_setleds_rgbw(struct cRGBW *ledarray, uint16_t leds) {
  ws2812_sendarray_mask((uint8_t*)ledarray, leds<<2, _BV(LED_DATA_PIN));
  _delay_us(LED_RESETTIME);
}

void ws2812_sendarray(uint8_t *data, uint16_t datlen) {
  ws2812_sendarray_mask(data, datlen, _BV(LED_DATA_PIN));
}

#define w_zeropulse   350  // Timing in ns
#define w_onepulse    900
#define w_totalperiod 1250

#define w_fixedlow    2   // Fixed cycles used by the inner loop
#define w_fixedhigh   4
#define w_fixedtotal  8   

#define w_zerocycles    (((F_CPU/1000)*w_zeropulse          )/1000000) // Insert NOPs to match the timing, if possible
#define w_onecycles     (((F_CPU/1000)*w_onepulse    +500000)/1000000)
#define w_totalcycles   (((F_CPU/1000)*w_totalperiod +500000)/1000000)

#define w1 (w_zerocycles-w_fixedlow)          // w1 - nops between rising edge and falling edge - low
#define w2 (w_onecycles-w_fixedhigh-w1)       // w2   nops between fe low and fe high
#define w3 (w_totalcycles-w_fixedtotal-w1-w2) // w3   nops to complete loop

#if w1>0
  #define w1_nops w1
#else
  #define w1_nops  0
#endif

#define w_lowtime ((w1_nops+w_fixedlow)*1000000)/(F_CPU/1000)

#if w2>0
#define w2_nops w2
#else
#define w2_nops  0
#endif

#if w3>0
#define w3_nops w3
#else
#define w3_nops  0
#endif

#define w_nop1  "nop      \n\t"
#ifdef INTERRUPT_DISABLE
#define w_nop2  "brid .+0 \n\t"
#else
#define w_nop2  "brtc .+0 \n\t"
#endif
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

void inline ws2812_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t maskhi) {
  uint8_t curbyte,ctr,masklo;
  uint8_t sreg_prev;
  
  WS2812_DDRREG |= maskhi;
  
  masklo	=~maskhi&WS2812_PORTREG;
  maskhi |=        WS2812_PORTREG;
  
  sreg_prev=SREG;
#ifdef INTERRUPT_DISABLE
  cli();  
#endif  

  while (datlen--) {
    curbyte=*data++;
    
    asm volatile(
    "       ldi   %0,8  \n\t"
#ifndef INTERRUPT_DISABLE
    "       clt         \n\t"
#endif
    "loop%=:            \n\t"
    "       out   %2,%3 \n\t"    //  '1' [01] '0' [01] - re
#if (w1_nops&1)
w_nop1
#endif
#if (w1_nops&2)
w_nop2
#endif
#if (w1_nops&4)
w_nop4
#endif
#if (w1_nops&8)
w_nop8
#endif
#if (w1_nops&16)
w_nop16
#endif
    "       sbrs  %1,7  \n\t"    //  '1' [03] '0' [02]
    "       out   %2,%4 \n\t"    //  '1' [--] '0' [03] - fe-low
    "       lsl   %1    \n\t"    //  '1' [04] '0' [04]
#if (w2_nops&1)
  w_nop1
#endif
#if (w2_nops&2)
  w_nop2
#endif
#if (w2_nops&4)
  w_nop4
#endif
#if (w2_nops&8)
  w_nop8
#endif
#if (w2_nops&16)
  w_nop16 
#endif
    "       out   %2,%4 \n\t"    //  '1' [+1] '0' [+1] - fe-high
#if (w3_nops&1)
w_nop1
#endif
#if (w3_nops&2)
w_nop2
#endif
#if (w3_nops&4)
w_nop4
#endif
#if (w3_nops&8)
w_nop8
#endif
#if (w3_nops&16)
w_nop16
#endif

    "       dec   %0    \n\t"    //  '1' [+2] '0' [+2]
    "       brne  loop%=\n\t"    //  '1' [+3] '0' [+4]
    :	"=&d" (ctr)
    :	"r" (curbyte), "I" (_SFR_IO_ADDR(WS2812_PORTREG)), "r" (maskhi), "r" (masklo)
    );
  }
  
  SREG=sreg_prev;
}
