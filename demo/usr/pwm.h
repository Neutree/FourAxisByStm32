#ifndef _PWM_H
#define _PWM_H
# include "stm32f10x.h"
#define MotorChannel1 TIM4->CCR1
#define MotorChannel2 TIM4->CCR2
#define MotorChannel3 TIM4->CCR3
#define MotorChannel4 TIM4->CCR4
#define MotorTimer TIM4

void PWMConfig(void);
void PWMChangeDuty(double duty , TIM_TypeDef* TIMx,u8 Channel);
void PWMChangeValue(u16 duty , TIM_TypeDef* TIMx,u8 Channel);
	
#endif
