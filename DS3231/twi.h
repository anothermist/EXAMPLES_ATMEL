#ifndef TWI_H_
#define TWI_H_

#include "main.h"

#define TWI_TIMEOUT 1600

#define TWI_START		0x08
#define TWI_RSTART		0x10
#define TWIT_ADDR_ACK	0x18
#define TWIT_ADDR_NACK	0x20
#define TWIT_DATA_ACK	0x28
#define TWIT_DATA_NACK	0x30

#define TWIR_ADDR_ACK	0x40
#define TWIR_ADDR_NACK	0x48
#define TWIR_DATA_ACK	0x50
#define TWIR_DATA_NACK	0x58

#define TWI_ERROR		0x38
#define TWI_NONE		0xF8

enum {
	TWI_OK,
	TWI_ERROR_START,
	TWI_ERROR_RSTART,
	TWI_NACK
};


void twi_init(unsigned long speed);
unsigned char twi_read(unsigned char addr, unsigned char reg, unsigned char *data, unsigned int len);
unsigned char twi_write(unsigned char addr, unsigned char reg, unsigned char *data, unsigned int len);

#endif /* TWI_H_ */