#ifndef UART_H_
#define UART_H_

#include "main.h"

#define CHAR 0
#define INT  1
#define LONG 2

#define TX_NEWLINE {uartTransmitByte(0x0d); uartTransmitByte(0x0a);}

void uartInit();
unsigned char uartReceiveByte();
void uartTransmitByte(unsigned char);
void uartTransmitString(unsigned char*);
void uartTransmitString_F(const char*);
void uartTransmitHex(unsigned char dataType, uint32_t data);
void uartNewLine();

#endif
