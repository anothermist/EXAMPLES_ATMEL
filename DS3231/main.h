#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#define F_SCL     400000
#define UART_BAUD   9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "uart.h"
#include "twi.h"
#include "ds3231.h"

#endif /* MAIN_H_ */
