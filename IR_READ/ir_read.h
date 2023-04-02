#ifndef IR_READ_H_
#define IR_READ_H_

#include "main.h"

#define ENABLED_PROTOCOL_NEC
#define ENABLED_PROTOCOL_RC5
#define ENABLED_PROTOCOL_SIRC

#define IR_PIN PINB
#define IR_PIN_NUM PINB5
#define IR_PORT PORTB

#define IR_ENABLE_PULLUP 1

#define NEC_REPEAT_RATE 5
#define RC5_REPEAT_RATE 5
#define SIRC_REPEAT_RATE 5

#define USED_TIMER 0

#if USED_TIMER == 0
#define TIMER_PRESCALER 1024
#define TIMER_INIT() TCCR0B = _BV(CS00) | _BV(CS02)
#define TIMER_REG TCNT0
#endif

#if USED_TIMER == 1
#define TIMER_PRESCALER 8
#define TIMER_INIT() TCCR1B = _BV(CS11)
#define TIMER_REG TCNT1
#endif

// Maximal time is 47407us for 16bit Timer1 & 23000us for 8bit Timer0
#define CONV(x) ((F_CPU/TIMER_PRESCALER)/(1000000/(x)))

#define IR_HIGH  (IR_PIN & _BV(IR_PIN_NUM))
#define IR_LOW (!(IR_PIN & _BV(IR_PIN_NUM)))
#define IR_VAL (IR_PIN & _BV(IR_PIN_NUM))

void irr_init();
unsigned int irr_decode();

unsigned int irr_protocol_NEC(unsigned int code);
unsigned int irr_protocol_RC5(unsigned int code);
unsigned int irr_protocol_SIRC(unsigned int code);

#endif /* IR_READ_H_ */
