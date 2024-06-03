/**
 * I2C.h
 *
 *  Created on: Fri May 26 2023
 *  Author    : Abdullah Darwish
 */

#ifndef I2C_H
#define I2C_H
#include "Std_Types.h"


void I2C1_Init(void);
void I2C1_Start(void);
void I2C1_Stop(void);
void I2C1_MasterTxAddr(uint8 SlaveAddr);
void I2C1_MasterTxSingleData(uint8 Data);
void I2C1_MasterTxMultiData(uint8 DataPtr[], uint32 Size);
void I2C1_MasterRxMulti(uint8 SlaveAddr, uint8* Buffer, uint8 Size); 
#endif /* I2C_H */
