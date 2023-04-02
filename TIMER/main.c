#include "main.h"

long long sec = 0, sec_last;

int main(void) {
	
	uart_init(9600, 0);
	millis_timer_1_init();

	while (1) {
		
		sec = uptime_second();

		if (sec_last != sec) {
			sec_last = sec;
			
			char string[16];
			snprintf(string, 16, "\rUPTIME: %06d", (unsigned int)sec);
			uart_send_string(string);
		}
	}
}

