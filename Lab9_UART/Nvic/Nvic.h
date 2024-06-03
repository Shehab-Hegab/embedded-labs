/**
 * Nvic.h
 *
 *  Created on: Mon May 13 2024
 *  Author    : Abdallah Darwish
 */

#ifndef NVIC_H
#define NVIC_H

#include "Std_Types.h"

void Nvic_EnableInterrupt(uint8 IRQn);

void Nvic_DisableInterrupt(uint8 IRQn);

#endif /* NVIC_H */
