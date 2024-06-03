/*
 * Uart.c
 *
 *  Created on: May 20, 2024
 *  Author    : abdallah darwish
 */

#include "Usart.h"
#include <avr/io.h>

void Usart_Init(void) {
	UCSRB = (1 << TXEN);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0) | (1 << URSEL);
	UBRRL = 0x33;

}

void Usart_Transmit(uint8 ch) {
	while (!(UCSRA & (1 << UDRE)))
		; //is empty
	UDR = ch;
}
