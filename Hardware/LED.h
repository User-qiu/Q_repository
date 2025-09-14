#ifndef _LED_H_
#define _LED_H_



void LED_Init(void);
void Set_LED1(uint8_t LED);
void Set_LED2(uint8_t LED);

void LED3_ON(void);
void LED3_OFF(void);

void LED1_Turn(void);
void LED2_Turn(void);

uint8_t Get_LED_Output(uint16_t Pin);



void LED_Tick(void);
void LED_SetMode(uint8_t Mode);


#endif
