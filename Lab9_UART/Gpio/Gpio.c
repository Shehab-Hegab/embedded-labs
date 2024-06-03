/**
 * Gpio.c
 *
 *  Created on: Tue Apr 11 2023
 *  Author    : Abdullah Darwish
 */

#include "Gpio.h"

#include "Gpio_Private.h"

uint32 GPIO_Addresses[2] = { 0x40020000, 0x40020400 };

#define GPIO_REG(REG_ID, PORT_ID) ((uint32*)((PORT_ID) + (REG_ID)))

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode,
		uint8 DefaultState) {
	uint8 PortId = PortName - GPIO_A;
	GpioType * gpioReg =  GPIO_Addresses[PortId];

	uint8 OutputState = DefaultState & 0x1;
	uint8 InputState = DefaultState >> 1;

	gpioReg->GPIO_MODER &= ~(0x3 << (2 * PinNum));
	gpioReg->GPIO_MODER |= (PinMode << (2 * PinNum));

	gpioReg->GPIO_OTYPER  &= ~(0x01 << PinNum);
	gpioReg->GPIO_OTYPER |= (OutputState << PinNum);

	gpioReg->GPIO_PUPDR &= ~(0x3 << (2 * PinNum));
	gpioReg->GPIO_PUPDR |= (InputState << (2*PinNum));
}

void Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data) {
	uint8 PortId = PortName - GPIO_A;
	GpioType * gpioReg =  GPIO_Addresses[PortId];
	gpioReg->GPIO_ODR &= ~(0x01 << PinNum);
	gpioReg->GPIO_ODR |= (Data << PinNum);
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum) {
	uint8 data = 0;
	uint8 PortId = PortName - GPIO_A;
	GpioType * gpioReg =  GPIO_Addresses[PortId];
	data = (gpioReg->GPIO_IDR & (1 << PinNum)) >> PinNum;
	return data;
}
