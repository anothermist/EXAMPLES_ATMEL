#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

#define EEPROM_SIZE 1023

enum {
	EEPROM_OK,
	EEPROM_WRITE_FAIL,
	EEPROM_INVALID_ADDR
};

unsigned char EEPROM_read(unsigned int uiAddress, unsigned char *data);
unsigned char EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_update(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read_batch(unsigned int uiAddress, void *data, unsigned int len);
unsigned char EEPROM_update_batch(unsigned int uiAddress, void *data, unsigned int len);

#endif /* EEPROM_H_ */
