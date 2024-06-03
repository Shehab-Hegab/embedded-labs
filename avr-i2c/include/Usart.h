/*
 * Uart.h
 *
 *  Created on: May 20, 2024
 *  Author    : abdallah darwish
 */

#ifndef USART_H_
#define USART_H_

#include "Std_Types.h"

void Usart_Init(void);

void Usart_Transmit(uint8 ch);

#endif /* USART_H_ */
