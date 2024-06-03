/**
 * Usart.h
 *
 *  Created on: Wed May 24 2023
 *  Author    : Abdullah Darwish
 */

#ifndef USART_H
#define USART_H
#include "Std_Types.h"

void Usart2_Init(void);

uint8 Usart2_TransmintByte(uint8 Byte);

uint8 Usart2_RecieveByte(void);

void Usart2_TransmitString(const char* Str);

#endif /* USART_H */
