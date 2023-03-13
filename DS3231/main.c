#include "main.h"

unsigned int rtc_Sec, rtc_Min, rtc_Hrs, rtc_WDay, rtc_Date, rtc_Month, rtc_Year,
last_Sec;

int main(void) {
	uartInit();
	TWI_Init();
	
 	//DS3231_setSec(0);
 	//DS3231_setMin(25);
 	//DS3231_setHrs(9);
 	//DS3231_setWDay(1);
 	//DS3231_setDate(13);
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

			char time_string[26];
			snprintf(time_string, 26, "TIME %02d:%02d:%02d %02d %02d %02d %02d",
			rtc_Hrs, rtc_Min, rtc_Sec, rtc_WDay, rtc_Date, rtc_Month, rtc_Year);
			uartTransmitString(time_string); uartNewLine();
			
		}
	}
}
