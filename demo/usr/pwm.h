#ifndef _PWM_H
#define _PWM_H
# include "stm32f10x.h"
#define MotorChannel1 TIM4->CCR1
#define MotorChannel2 TIM4->CCR2
#define MotorChannel3 TIM4->CCR3
#define MotorChannel4 TIM4->CCR4
#define MotorTimer TIM4
#define MotorPWMT  ((MotorTimer->PSC+1)*(MotorTimer->ARR+1)/72000.0)  //PWM输出的周期 单位：ms  


void PWMConfig(void);
void PWMChangeDuty(double duty , TIM_TypeDef* TIMx,u8 Channel);
void PWMChangeValue(u16 duty , TIM_TypeDef* TIMx,u8 Channel);
	
#endif
