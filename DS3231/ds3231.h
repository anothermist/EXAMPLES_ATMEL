#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#include "main.h"
#include "math.h"

#define DS3231_ADDRESS		0xD0

unsigned int decToBcd(unsigned int val);
unsigned int bcdToDec(unsigned int val);
void DS3231_Update(void);
unsigned char DS3231_getSec(void);
unsigned char DS3231_getMin(void);
unsigned char DS3231_getHrs(void);
unsigned char DS3231_getWDay(void);
unsigned char DS3231_getDate(void);
unsigned char DS3231_getMonth(void);
unsigned char DS3231_getYear(void);
unsigned char DS3231_getAlarm1Sec(void);
unsigned char DS3231_getAlarm1Min(void);
unsigned char DS3231_getAlarm1Hour(void);
unsigned char DS3231_getAlarm1WeekDay(void);
unsigned char DS3231_getAlarm1Date(void);
unsigned char DS3231_getAlarm2Min(void);
unsigned char DS3231_getAlarm2Hour(void);
unsigned char DS3231_getAlarm2WeekDay(void);
unsigned char DS3231_getAlarm2Date(void);
double DS3231_getTemp(void);
void DS3231_setSec(unsigned char value);
void DS3231_setMin(unsigned char value);
void DS3231_setHrs(unsigned char value);
void DS3231_setWDay(unsigned char value);
void DS3231_setDate(unsigned char value);
void DS3231_setMonth(unsigned char value);
void DS3231_setYear(unsigned char value);
void DS3231_setAlarm1Sec(unsigned char value);
void DS3231_setAlarm1Min(unsigned char value);
void DS3231_setAlarm1Hour(unsigned char value);
void DS3231_setAlarm1Day(unsigned char value);
void DS3231_setAlarm1Date(unsigned char value);
void DS3231_setAlarm2Min(unsigned char value);
void DS3231_setAlarm2Hour(unsigned char value);
void DS3231_setAlarm2Day(unsigned char value);
void DS3231_setAlarm2Date(unsigned char value);
unsigned long DS3231_getUnix(unsigned long zoneCorrection);
float DS3231_getMoonDay(void);

#endif /* INC_DS3231_H_ */
