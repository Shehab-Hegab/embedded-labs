/**
 * main.c
 *
 *  Created on: Fri May 17 2024
 *  Author    : Abdallah Darwish
 */
#include "Bit_Operations.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Std_Types.h"
#include "Usart.h"
#include "Utils.h"
int main() {
  Rcc_Init();
  Rcc_Enable(RCC_GPIOA);
  Rcc_Enable(RCC_USART2);
  Usart2_Init();

  uint8 data = 0;
  while (1) {
    data = Usart2_RecieveByte();
    if (data == '1') {
      Usart2_TransmitString("Hello\r\n");
    }
    if (data == '2') {
      Usart2_TransmitString("Welcome\r\n");
    }
  }
}
