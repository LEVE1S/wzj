#ifndef __BUZZER_H
#define __BUZZER_H

void Buzzer_Init(void);
void Timer_Init(void);
void Buzzer_OFF(void);
void Buzzer_ON(void);
extern volatile uint8_t Buzzer_Flag;
extern volatile uint16_t Counter;

#endif
