/*
 * I2c.h
 *
 *  Created on: May 20, 2024
 *  Author    : abdallah darwish
 */

#ifndef I2C_H_
#define I2C_H_

#include "Std_Types.h"

#define ACK 1
#define NACk 0

#define W 0
#define R 1

void I2C_MasterInit();
void I2C_Start(void);
void I2C_Stop(void);

void I2C_SendSlaveAddress(uint8 address, uint8 WR);
void I2C_SendData(uint8 data);
void I2C_GetData(uint8* dataPtr, uint8 ack);

#endif /* I2C_H_ */
