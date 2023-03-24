#include "ds3231.h"
#include "twi.h"

unsigned char rtcBuffer[19];

unsigned int decToBcd(unsigned int val) { return ((val / 10 * 16) + (val % 10)); }
unsigned int bcdToDec(unsigned int val) { return ((val / 16 * 10) + (val % 16)); }

void DS3231_Update(void) { twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer)); }

unsigned char DS3231_getSec(void)           { return bcdToDec(rtcBuffer[0]); }
unsigned char DS3231_getMin(void)           { return bcdToDec(rtcBuffer[1]); }
unsigned char DS3231_getHrs(void)           { return bcdToDec(rtcBuffer[2]); }
unsigned char DS3231_getWDay(void)          { return bcdToDec(rtcBuffer[3]); }
unsigned char DS3231_getDate(void)          { return bcdToDec(rtcBuffer[4]); }
unsigned char DS3231_getMonth(void)         { return bcdToDec(rtcBuffer[5]); }
unsigned char DS3231_getYear(void)          { return bcdToDec(rtcBuffer[6]); }
unsigned char DS3231_getAlarm1Sec(void)     { return bcdToDec(rtcBuffer[7]); }
unsigned char DS3231_getAlarm1Min(void)     { return bcdToDec(rtcBuffer[8]); }
unsigned char DS3231_getAlarm1Hour(void)    { return bcdToDec(rtcBuffer[9]); }
unsigned char DS3231_getAlarm1WeekDay(void) { return bcdToDec(rtcBuffer[10]); }
unsigned char DS3231_getAlarm1Date(void)    { return bcdToDec(rtcBuffer[11]); }
unsigned char DS3231_getAlarm2Min(void)     { return bcdToDec(rtcBuffer[12]); }
unsigned char DS3231_getAlarm2Hour(void)    { return bcdToDec(rtcBuffer[13]); }
unsigned char DS3231_getAlarm2WeekDay(void) { return bcdToDec(rtcBuffer[14]); }
unsigned char DS3231_getAlarm2Date(void)    { return bcdToDec(rtcBuffer[15]); }

void DS3231_setSec(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[0] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setMin(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[1] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setHrs(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[2] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setWDay(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[3] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setDate(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[4] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setMonth(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[5] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setYear(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[6] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm1Sec(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[7] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm1Min(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[8] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm1Hour(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[9] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm1Day(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[10] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm1Date(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[11] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm2Min(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[12] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm2Hour(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[13] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm2Day(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[14] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}

void DS3231_setAlarm2Date(unsigned char value) {
	twi_data_read(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
	rtcBuffer[16] = decToBcd(value);
	twi_data_write(DS3231_ADDRESS, 0x00, rtcBuffer, sizeof(rtcBuffer));
}
