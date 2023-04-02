#include "timer.h"

static long long millis = 0, second = 0;
	
ISR(TIMER1_COMPA_vect) { millis++; if (millis % 1000 == 0) second++; }

void millis_timer_1_init() {
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	OCR1A  = (F_CPU / 1000) -1;
	TCCR1B |=  (1 << WGM12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	sei();
}

long long uptime_millis() { return millis; }
long long uptime_second() { return second; }
