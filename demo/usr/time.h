#ifndef _TIME_H
#define _TIME_H
#include "stm32f10x.h"
#include "usart.h"

//����
extern u16 timeCount_10ms;
extern u8 flag10ms;
///////////////////////////////////////////////

//��ʱ��3  ��ʱ����
void TIM3_Configuration(void);




#endif
