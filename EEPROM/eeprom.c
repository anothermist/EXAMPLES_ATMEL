#include "eeprom.h"

unsigned char EEPROM_read(unsigned int uiAddress, unsigned char *data) {
	if (uiAddress > EEPROM_SIZE) EEPROM_INVALID_ADDR;
	
	while (EECR & (1<<EEPE));          // Wait for completion of previous write
	EEARH = (uiAddress & 0xFF00) >> 8; // Set up address register
	EEARL = (uiAddress & 0x00FF);
	EECR |= (1<<EERE);                 // Start eeprom read by writing EERE
	*data = EEDR;                      // Return data from Data Register
	return EEPROM_OK;
}

unsigned char EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
	if (uiAddress > EEPROM_SIZE) return EEPROM_INVALID_ADDR;
	
	while(EECR & (1<<EEPE));           // Wait for completion of previous write
	EEARH = (uiAddress & 0xFF00) >> 8; // Set up address and Data Registers
	EEARL = (uiAddress & 0x00FF);
	EEDR = ucData;
	EECR |= (1<<EEMPE);                // Write logical one to EEMPE
	EECR |= (1<<EEPE);                 // Start eeprom write by setting EEPE
	return EEPROM_OK;
}

unsigned char EEPROM_update(unsigned int uiAddress, unsigned char ucData) {
	unsigned char err = EEPROM_OK;
	if (uiAddress > EEPROM_SIZE) return EEPROM_INVALID_ADDR;
	unsigned char value = 0;
	
	err = EEPROM_read(uiAddress, &value);
	if (err != EEPROM_OK) return err;
	if (value == ucData)  return EEPROM_OK;
	
	err = EEPROM_write(uiAddress, ucData);
	if (err != EEPROM_OK) return err;
	
	err = EEPROM_read(uiAddress, &value);
	if (err != EEPROM_OK) return err;
	if(value != ucData) return EEPROM_WRITE_FAIL; return EEPROM_OK;
}

unsigned char EEPROM_update_batch(unsigned int uiAddress, void *data, unsigned int len) {
	unsigned int i = 0;
	unsigned char err = EEPROM_OK;
	unsigned char *data_cast = (unsigned char *) data;
	
	for (i = 0; i < len; i++) {
		err = EEPROM_update(uiAddress + i, data_cast[i]);
		if (err != EEPROM_OK) return err;
	}
	return EEPROM_OK;
}

unsigned char EEPROM_read_batch(unsigned int uiAddress, void *data, unsigned int len) {
	unsigned int i = 0;
	unsigned char err = EEPROM_OK;
	unsigned char *data_cast = (unsigned char *) data;
	
	for (i = 0; i < len; i++) {
		err = EEPROM_read(uiAddress + i, &data_cast[i]);
		if (err != EEPROM_OK) return err;
	}
	return EEPROM_OK;
}
