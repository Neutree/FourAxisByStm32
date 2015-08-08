#ifndef _TIME_H
#define _TIME_H
#include "stm32f10x.h"
#include "usart.h"

//变量
extern u16 timeCount_10ms;
extern u8 flag10ms;
///////////////////////////////////////////////

//定时器3  定时配置
void TIM3_Configuration(void);




#endif
