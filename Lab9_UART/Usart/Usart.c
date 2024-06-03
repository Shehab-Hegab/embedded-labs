/**
 * Usart.c
 *
 *  Created on: Wed May 24 2023
 *  Author    : Abdullah Darwish
 */

#include "stm32f401xe.h"
#include "Gpio.h"
#include "Std_Types.h"
#include "Utils.h"

#define OK  0
#define NOK 1

void Usart2_Init(void) {
  Gpio_ConfigPin(GPIO_A, 2, GPIO_AF, GPIO_PUSH_PULL);
  Gpio_ConfigPin(GPIO_A, 3, GPIO_AF, GPIO_PUSH_PULL);

  GPIOA->AFR[0] &= ~(0xff << 4 * 2);
  GPIOA->AFR[0] |= 0x77 << 4 * 2;


  USART2->CR1 &= ~(1 << USART_CR1_M_Pos); // 8-bit word length

  USART2->CR2 &= ~(USART_CR2_STOP);  // 1-stop bit at end

  USART2->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // 16 over sampling

  USART2->BRR = 0x683;  // Baud Rate 9600

  /* Enable Transmission block */
  USART2->CR1 |= (1 << USART_CR1_TE_Pos);

  /* Enable Receive block */
  USART2->CR1 |= (1 << USART_CR1_RE_Pos);

  /* Enable USART2 */
  USART2->CR1 |= (1 << USART_CR1_UE_Pos);
}

uint8 Usart2_TransmintByte(uint8 Byte){
  if (USART2->SR & USART_SR_TXE) {
    USART2->DR = Byte;
    while (!(USART2->SR & USART_SR_TC));
    USART2->SR &= ~(1 << USART_SR_TC_Pos);  // Clearing TC bit
    return OK;
  }
  return NOK;
}

uint8 Usart2_RecieveByte(void){
   while (!(USART2->SR & USART_SR_RXNE));
   return USART2->DR;
}

void Usart2_TransmitString(const char* Str) {
  uint32 i = 0;
  uint8 transmitResult = -1;
  while (Str[i] != '\0') {
    transmitResult = Usart2_TransmintByte(Str[i]);
    if(transmitResult == OK){
      i++;
    }
  }
}
