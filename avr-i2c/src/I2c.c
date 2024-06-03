/*
 * I2c.c
 *
 *  Created on: May 20, 2024
 *  Author    : abdallah darwish
 */

#include <avr/io.h>
#include "I2c.h"
#define PRESCALAR 1

void I2C_MasterInit() {
	TWSR=0x00; //set prescaler bits to zero
	TWBR=0x47; //SCL frequency is 50K for XTAL = 8M
	TWCR=0x04; //enable the TWI module
}

void I2C_Start(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	while ((TWCR & (1 << TWINT)) ==  0)
		; //wait to finish
}

void I2C_Stop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void I2C_SendSlaveAddress(uint8 address, uint8 WR) {
	I2C_SendData(address | WR);
}

void I2C_SendData(uint8 data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0)
			; //wait to finish
}

void I2C_GetData(uint8* dataPtr, uint8 ack){
	if (ack == ACK){
		TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWEA);
	} else {
		TWCR = (1<< TWINT)|(1<<TWEN);
	}
	while ((TWCR & (1 <<TWINT)) == 0);
	*dataPtr = TWDR;
}


