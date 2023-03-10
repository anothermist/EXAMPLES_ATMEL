#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#include "main.h"
#include "math.h"

#define DS3231_ADDRESS		0xD0

unsigned int decToBcd(unsigned int val);
unsigned int bcdToDec(unsigned int val);
void DS3231_Update(void);
uint8_t DS3231_getSec(void);
uint8_t DS3231_getMin(void);
uint8_t DS3231_getHrs(void);
uint8_t DS3231_getWDay(void);
uint8_t DS3231_getDate(void);
uint8_t DS3231_getMonth(void);
uint8_t DS3231_getYear(void);
uint8_t DS3231_getAlarm1Sec(void);
uint8_t DS3231_getAlarm1Min(void);
uint8_t DS3231_getAlarm1Hour(void);
uint8_t DS3231_getAlarm1WeekDay(void);
uint8_t DS3231_getAlarm1Date(void);
uint8_t DS3231_getAlarm2Min(void);
uint8_t DS3231_getAlarm2Hour(void);
uint8_t DS3231_getAlarm2WeekDay(void);
uint8_t DS3231_getAlarm2Date(void);
//double DS3231_getTemp(void);
void DS3231_setSec(uint8_t value);
void DS3231_setMin(uint8_t value);
void DS3231_setHrs(uint8_t value);
void DS3231_setWDay(uint8_t value);
void DS3231_setDate(uint8_t value);
void DS3231_setMonth(uint8_t value);
void DS3231_setYear(uint8_t value);
void DS3231_setAlarm1Sec(uint8_t value);
void DS3231_setAlarm1Min(uint8_t value);
void DS3231_setAlarm1Hour(uint8_t value);
void DS3231_setAlarm1Day(uint8_t value);
void DS3231_setAlarm1Date(uint8_t value);
void DS3231_setAlarm2Min(uint8_t value);
void DS3231_setAlarm2Hour(uint8_t value);
void DS3231_setAlarm2Day(uint8_t value);
void DS3231_setAlarm2Date(uint8_t value);
//unsigned long DS3231_getUnix(unsigned long zoneCorrection);
//float DS3231_getMoonDay(void);

#endif /* INC_DS3231_H_ */
