/**
 * I2C.c
 *
 *  Created on: Fri May 26 2023
 *  Author    : Abdullah Darwish
 */

#include "Gpio.h"
#include "I2C.h"
#include "Utils.h"
#include "stm32f401xe.h"

#define I2C1_RCC_EN() (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN_Msk)
#define I2C1_AF_EN() (GPIOB->AFR[0] |= (0x44 << (6 * 4)))

#define I2C1_START_GEN() (I2C1->CR1 |= I2C_CR1_START_Msk)
#define I2C1_STOP_GEN() (I2C1->CR1 |= I2C_CR1_STOP_Msk)
#define I2C1_MASTER_ACK() (I2C1->CR1 |= (I2C_CR1_ACK_Msk))
#define I2C1_MASTER_NACK() (I2C1->CR1 &= ~(I2C_CR1_ACK_Msk))

void I2C1_Init(void) {
  GPIO_Init(GPIO_B, 6, GPIO_AF, GPIO_OPEN_DRAIN);
  GPIO_Init(GPIO_B, 7, GPIO_AF, GPIO_OPEN_DRAIN);
  I2C1_AF_EN();

  I2C1->CR1 &= ~(I2C_CR1_PE_Msk);

  /* Standard mode 2MHZ Peripheral freq */
  I2C1->CR2 &= ~(I2C_CR2_FREQ_Msk);
  I2C1->CR2 |= 16;

  /* 100 KHz  master clk*/
  I2C1->CCR = 0;
  I2C1->CCR |= 80;

  /* Sm mode, the maximum allowed SCL rise time is 1000 ns. */
  I2C1->TRISE = 17;

  /* Enable Interrupt */
  //   I2C1_CR2 |= I2C_CR2_ITEVTEN_Msk;
  //   I2C1_CR2 |= I2C_CR2_ITBUFEN_Msk;
  //   NVIC_ISER0 = (1 << 31);

  /* Enable I2C1 */
  I2C1->CR1 |= I2C_CR1_PE_Msk;
}

void I2C1_Start(void) {
  I2C1_START_GEN();
  while (!(I2C1->SR1 & I2C_SR1_SB_Msk));
}

void I2C1_Stop(void) {
  I2C1_STOP_GEN();
  for (int k = 0; k < 100; k++)
    ;
}
void I2C1_MasterTxAddr(uint8 SlaveAddr) {
  I2C1->DR = SlaveAddr;
  while (!(I2C1->SR1 & I2C_SR1_ADDR_Msk))
    ;
  /* Flag cleared by reading two registers */
  I2C1->SR1;
  I2C1->SR2;
}

void I2C1_MasterTxSingleData(uint8 Data) {
  while (!(I2C1->SR1 & I2C_SR1_TXE_Msk))
    ;
  I2C1->DR = Data;
  while (!(I2C1->SR1 & I2C_SR1_BTF_Msk))
    ;
}

void I2C1_MasterTxMultiData(uint8 DataPtr[], uint32 Size) {
  while (!(I2C1->SR1 & I2C_SR1_TXE_Msk))
    ;
  while (Size) {
    while (!(I2C1->SR1 & I2C_SR1_TXE_Msk))
      ;
    I2C1->DR = *DataPtr;
    DataPtr++;
    Size--;
  }
  while (!(I2C1->SR1 & I2C_SR1_BTF_Msk))
    ;
}



void I2C1_MasterRxMulti(uint8 SlaveAddr, uint8* Buffer, uint8 Size) {
  I2C1->DR = SlaveAddr;

  while (!(I2C1->SR1 & I2C_SR1_ADDR_Msk))
    ;
  /* Flag cleared by reading two registers */
  if (Size == 1) {
    I2C1->CR1 &= ~(I2C_CR1_ACK_Msk);
    I2C1->SR1;
    I2C1->SR2;
    I2C1_STOP_GEN();
    while (!(I2C1->SR1 & I2C_SR1_RXNE_Msk))
      ;

    *Buffer = I2C1->DR;

  } else {
    while (Size > 2) {
      while (!(I2C1->SR1 & I2C_SR1_RXNE_Msk))
        ;
      *Buffer = I2C1->DR;
      Buffer++;
      Size--;
    }
    /* Size == 2 */
    while (!(I2C1->SR1 & I2C_SR1_RXNE_Msk))
      ;
    *Buffer = I2C1->DR;
    Buffer++;
    Size--;
    I2C1->CR1 &= ~(I2C_CR1_ACK_Msk);
    I2C1_STOP_GEN();
    while (!(I2C1->SR1 & I2C_SR1_RXNE_Msk))
      ;
    *Buffer = I2C1->DR;
  }
}