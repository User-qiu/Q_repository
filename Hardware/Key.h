#ifndef _key_h_
#define _key_h_

#include "stm32f10x.h"                  // Device header


void Key_Init(void);
uint8_t Key_GetNum(void);

uint8_t Key_GetStatus(void);
void Key_Tick(void);

#endif
