#include "main.h"

unsigned char rtc_Sec, rtc_Min, rtc_Hrs, rtc_WDay, rtc_Date, rtc_Month, rtc_Year, last_Sec;

int main(void) {
	char start[] = "\n\rUART OK\n\r";
	
	uart_init(9600, 0);
	twi_init();

	uart_send_string(start);

	//DS3231_setSec(0);
	//DS3231_setMin(44);
	//DS3231_setHrs(23);
	//DS3231_setWDay(5);
	//DS3231_setDate(24);
	//DS3231_setMonth(3);
	//DS3231_setYear(23);


	while (1) {
		
		DS3231_Update();
		rtc_Sec = DS3231_getSec();
		
		if (last_Sec != rtc_Sec) {
			last_Sec = rtc_Sec;
			rtc_Min = DS3231_getMin();
			rtc_Hrs = DS3231_getHrs();
			rtc_WDay = DS3231_getWDay();
			rtc_Date = DS3231_getDate();
			rtc_Month = DS3231_getMonth();
			rtc_Year = DS3231_getYear();

			char time_string[29];
			snprintf(time_string, 29, "\rTIME %02d:%02d:%02d %02d %02d %02d %02d",
			rtc_Hrs, rtc_Min, rtc_Sec, rtc_WDay, rtc_Date, rtc_Month, rtc_Year);
			uart_send_string(time_string);
		}
		
	}
}
