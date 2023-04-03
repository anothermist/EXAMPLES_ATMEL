#include "ir_read.h"

unsigned char repeatCount = 0;
unsigned int code = 0;
unsigned int time;
unsigned char protocolLetter;

void irr_init() {
	TIMER_INIT();
	if (IR_ENABLE_PULLUP)
	IR_PORT |= _BV(IR_PIN_NUM);
}

unsigned int irr_decode() {
	time = TIMER_REG;
	TIMER_REG = 0;

	if (time > CONV(9000) && time < CONV(9800)) { // Between 9ms and 9.8ms => NEC protocol
		protocolLetter = 'N';
		#ifdef ENABLED_PROTOCOL_NEC
		code = irr_protocol_NEC(code);
		#endif
		} else if (time > CONV(800) && time < CONV(1200)) { // Between 0.8ms and 1.2ms => RC5 protocol
		protocolLetter = 'R';
		#ifdef ENABLED_PROTOCOL_RC5
		code = irr_protocol_RC5(code);
		#endif
		} else if (time > CONV(2000) && time < CONV(2800)) { // Between 2ms and 2.8ms => SIRC protocol
		protocolLetter = 'S';
		#ifdef ENABLED_PROTOCOL_SIRC
		code = irr_protocol_SIRC(code);
		#endif
		} else {
		protocolLetter = 'U';
	}
	unsigned int decoded = code;
	code = 0;
	return (decoded);
}

#ifdef ENABLED_PROTOCOL_NEC
unsigned int irr_protocol_NEC(unsigned int code) {
	unsigned char bitVal;
	unsigned int time;
	unsigned char i;
	unsigned int invertedCode = 0;
	static unsigned int lastCode = 0;

	while (IR_HIGH);/*
	if (TIMER_REG > CONV(5000))
	return 0;*/

	time = TIMER_REG;
	TIMER_REG = 0;

	IR_PORT ^= _BV(IR_PIN_NUM);
	
	if (time > CONV(4200)) { // 4200 us
		repeatCount = 0; // regular button press
		} else {
		if (++repeatCount == NEC_REPEAT_RATE) { // hold button press send last keycode
			repeatCount = 0;
			return lastCode;
		}
		return 0;
	}
	
	code = 0;
	
	for (i = 0; i < 32; i++) { // Read 32 data bits
		while (IR_LOW);
		/*	if (TIMER_REG > CONV(5000))
		return 0;*/
		while (IR_HIGH);/*
		if (TIMER_REG > CONV(5000))
		return 0;*/

		time = TIMER_REG;
		TIMER_REG = 0;
		
		if (time > CONV(1650)) { // 1650 us
			bitVal = 1;
			} else {
			bitVal = 0;
		}

		IR_PORT ^= _BV(IR_PIN_NUM);
		
		if ((i < 8) || (i >= 16 && i < 24)) {
			code = code << 1;
			code |= bitVal;
		}

		if ((i >= 8 && i < 16) || (i >= 24 && i < 32)) {
			invertedCode = invertedCode << 1;
			invertedCode |= bitVal;
		}
	}

	if (code != ~invertedCode)
	return 0;

	lastCode = code;
	return code;
}
#endif

#ifdef ENABLED_PROTOCOL_RC5
unsigned int irr_protocol_RC5(unsigned int code) {
	unsigned char repeatBit;
	unsigned char i;

	static unsigned int lastCode = 0;
	static unsigned char lastRepeatBit = 0;

	unsigned char errorBit;

	code = 0;

	while (TIMER_REG < CONV(3160)); // 3160 us offset from the first pulse
	TIMER_REG = 0;

	repeatBit = IR_VAL; // Read "repeat" bit
	IR_PORT ^= _BV(IR_PIN_NUM);

	// Move 1760us to the first data bit
	while (TIMER_REG < CONV(880));
	TIMER_REG = 0;

	for (i = 0; i < 11; i++) { // Read 12 data bits (5 address & 7 command)
		code = code << 1;
		IR_PORT ^= _BV(IR_PIN_NUM);
		errorBit = IR_VAL;

		//while (TIMER_REG < CONV(RC5_DELAY_0));
		//TIMER_REG = 0;

		// Read second half of bit, which has to be inverted
		// so we check whether the code is ok

		while (errorBit == IR_VAL)
		if (TIMER_REG > CONV(1000))
		return 0;

		TIMER_REG = 0;
		while (TIMER_REG < CONV(400));
		TIMER_REG = 0;

		IR_PORT ^= _BV(IR_PIN_NUM);
		
		if (IR_VAL)
		code |= 0x0001;

		if (IR_VAL && errorBit) // If the previous and current bit is the same - we have error code
		return 0;
		
		while (TIMER_REG < CONV(800));
		TIMER_REG = 0;
	}

	if (code == lastCode && repeatBit == lastRepeatBit) {
		if (++repeatCount == RC5_REPEAT_RATE) {
			repeatCount = 0;
			return code;
			} else {
			return 0;
		}
	}

	if (repeatBit != lastRepeatBit) {
		repeatCount = 0;
	}

	lastCode = code;
	lastRepeatBit = repeatBit;
	return code;
}
#endif

#ifdef ENABLED_PROTOCOL_SIRC
unsigned int irr_protocol_SIRC(unsigned int code) {
	unsigned int time;
	unsigned char i;
	static unsigned int lastCode = 0;

	code = 0;

	for (i = 0; i < 12; i++) { // Read 32 data bits
		while (IR_LOW)
		if (TIMER_REG > CONV(2000))
		return 0;
		while (IR_HIGH)
		if (TIMER_REG > CONV(2000))
		return 0;

		time = TIMER_REG;
		TIMER_REG = 0;

		if (time < CONV(400) || time > CONV(2000)) // error check - pulse length between 500-2000us
		return 0;

		code = code << 1;

		if (time > CONV(1440)) // 1440 us
		code |= 1;
	}
	
	if (code == lastCode) {
		if ((repeatCount++) == SIRC_REPEAT_RATE) {
			repeatCount = 0;
			return code;
			} else {
			return 0;
		}
	}
	lastCode = code;
	return code;
}
#endif
