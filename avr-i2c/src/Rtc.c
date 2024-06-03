/*
 * Rtc.c
 *
 *  Created on: May 20, 2024
 *  Author    : abdalladarwish
 */

#include "Rtc.h"
#include "I2c.h"

void Rtc_Init(void) {
	I2C_MasterInit();
	I2C_Start();
	I2C_SendSlaveAddress(0xD0, W);
	I2C_SendData(0x00);
	I2C_Stop();
}

void Rtc_GetTime(uint8 *h, uint8 *m, uint8 *s) {
	I2C_Start();
	I2C_SendSlaveAddress(0xD0, W);
	I2C_SendData(0x00);
	I2C_Stop();

	I2C_Start();
	I2C_SendSlaveAddress(0xD0, R);
	I2C_GetData(s, ACK);
	I2C_GetData(m, ACK);
	I2C_GetData(h, NACk);
	I2C_Stop();
}

void Rtc_SetTime(uint8 h, uint8 m, uint8 s) {
	I2C_Start();
	I2C_SendSlaveAddress(0xD0, W);
	I2C_SendData(0x00);  // set register pointer to 0x00
	I2C_SendData(s);
	I2C_SendData(m);
	I2C_SendData(h);
	I2C_Stop();
}
