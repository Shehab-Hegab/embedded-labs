/*
 * Rtc.h
 *
 *  Created on: May 20, 2024
 *  Author    : abdallah darwish
 */

#ifndef RTC_H_
#define RTC_H_

#include "Std_Types.h"

void Rtc_Init(void);

void Rtc_GetTime(uint8 *h, uint8 *m, uint8 *s);

void Rtc_SetTime(uint8 h, uint8 m, uint8 s);

#endif /* RTC_H_ */
