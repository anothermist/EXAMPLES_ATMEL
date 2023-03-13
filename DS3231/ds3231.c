#include "ds3231.h"
#include "twi.h"

uint8_t rtcBuffer[19], rtcBufferSet[17];

unsigned int decToBcd(unsigned int val) {
	return ((val / 10 * 16) + (val % 10));
}

unsigned int bcdToDec(unsigned int val) {
	return ((val / 16 * 10) + (val % 16));
}

void DS3231_Update(void) {
	TWI_SendByteByADDR(0, DS3231_ADDRESS);
	TWI_StartCondition();
	TWI_SendByte(0b11010001);
	
	for (uint8_t i = 0; i < 17; i++) rtcBuffer[i] = TWI_ReadByte();
	rtcBuffer[18] = TWI_ReadLastByte();
	TWI_StopCondition();
	
	for (uint8_t i = 0; i < 16; i++) rtcBufferSet[i+1] = rtcBuffer[i];
}

uint8_t DS3231_getSec(void) {
	return bcdToDec(rtcBuffer[0]);
}

uint8_t DS3231_getMin(void) {
	return bcdToDec(rtcBuffer[1]);
}

uint8_t DS3231_getHrs(void) {
	return bcdToDec(rtcBuffer[2]);
}

uint8_t DS3231_getWDay(void) {
	return bcdToDec(rtcBuffer[3]);
}

uint8_t DS3231_getDate(void) {
	return bcdToDec(rtcBuffer[4]);
}

uint8_t DS3231_getMonth(void) {
	return bcdToDec(rtcBuffer[5]);
}

uint8_t DS3231_getYear(void) {
	return bcdToDec(rtcBuffer[6]);
}

uint8_t DS3231_getAlarm1Sec(void) {
	return bcdToDec(rtcBuffer[7]);
}

uint8_t DS3231_getAlarm1Min(void) {
	return bcdToDec(rtcBuffer[8]);
}

uint8_t DS3231_getAlarm1Hour(void) {
	return bcdToDec(rtcBuffer[9]);
}

uint8_t DS3231_getAlarm1WeekDay(void) {
	return bcdToDec(rtcBuffer[10]);
}

uint8_t DS3231_getAlarm1Date(void) {
	return bcdToDec(rtcBuffer[11]);
}

uint8_t DS3231_getAlarm2Min(void) {
	return bcdToDec(rtcBuffer[12]);
}

uint8_t DS3231_getAlarm2Hour(void) {
	return bcdToDec(rtcBuffer[13]);
}

uint8_t DS3231_getAlarm2WeekDay(void) {
	return bcdToDec(rtcBuffer[14]);
}

uint8_t DS3231_getAlarm2Date(void) {
	return bcdToDec(rtcBuffer[15]);
}

//double DS3231_getTemp(void) {
//unsigned int tempMSB = rtcBuffer[17];
//unsigned int tempLSB = rtcBuffer[18];
//double t = 0.0;
//tempLSB >>= 6;
//tempLSB &= 0x03;
//t = ((double) tempLSB);
//t *= 0.25;
//t += tempMSB;
//return t;
//}

void DS3231_setSec(uint8_t value) {
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setMin(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	TWI_SendByte(rtcBuffer[0]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setHrs(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	TWI_SendByte(rtcBuffer[0]);
	TWI_SendByte(rtcBuffer[1]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setWDay(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 3; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setDate(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 4; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setMonth(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 5; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setYear(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 6; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm1Sec(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 7; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm1Min(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 8; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm1Hour(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 9; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm1Day(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 10; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm1Date(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 11; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm2Min(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 12; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm2Hour(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 13; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm2Day(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 14; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

void DS3231_setAlarm2Date(uint8_t value) {
	DS3231_Update();
	TWI_StartCondition();
	TWI_SendByte(DS3231_ADDRESS);
	TWI_SendByte(0);
	for (uint8_t i = 0; i < 15; i++) TWI_SendByte(rtcBuffer[i]);
	TWI_SendByte(decToBcd(value));
	TWI_StopCondition();
}

//unsigned long DS3231_getUnix(unsigned long zoneCorrection) {
//unsigned int timeYear = DS3231_getYear();
//unsigned int timeMonth = DS3231_getMonth();
//unsigned int timeDate = DS3231_getDate();
//unsigned int timeHour = DS3231_getHrs();
//unsigned int timeMin = DS3231_getMin();
//unsigned int timeSec = DS3231_getSec();
//
//const unsigned int dim[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//uint16_t dc;
//dc = timeDate;
//for (unsigned int i = 0; i < (timeMonth - 1); i++) dc += dim[i];
//if ((timeMonth > 2) && (((timeYear) % 4) == 0)) ++dc;
//dc = dc + (365 * (timeYear)) + (((timeYear) + 3) / 4) - 1;
//return ((((((dc * 24L) + timeHour) * 60) + timeMin) * 60) + timeSec) + 946684800 + zoneCorrection;
//}

//double normalize(double v) {
//v = v - floor(v);
//if (v < 0)
//v = v + 1;
//return v;
//}

//float DS3231_getMoonDay(void) {
//uint16_t Y = DS3231_getYear() + 2000;
//unsigned int M = DS3231_getMonth();
//unsigned int D = DS3231_getDate();
//float moonDay;
//double I;
//uint64_t YY, MM, K1, K2, K3, JD;
//YY = Y - floor((12 - M) / 10);
//MM = M + 9;
//if (MM >= 12) {
//MM = MM - 12;
//}
//K1 = floor(365.25 * (YY + 4712));
//K2 = floor(30.6 * MM + 0.5);
//K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;
//JD = K1 + K2 + D + 59;
//if (JD > 2299160) {
//JD = JD - K3;
//}
//I = normalize((JD - 2451550.1) / 29.530588853);
//moonDay = I * 29.53;
//return moonDay;
//}
