#ifndef _PWM_H
#define _PWM_H
# include "stm32f10x.h"
#define MotorChannel1 TIM4->CCR1
#define MotorChannel2 TIM4->CCR2
#define MotorChannel3 TIM4->CCR3
#define MotorChannel4 TIM4->CCR4
#define MotorTimer TIM4
#define MotorPWMT  2.5  //PWM输出的周期 单位：ms  //如果要修改值，要同时修改pwm.c中的pwm输出周期（频率）


void PWMConfig(void);
void PWMChangeDuty(double duty , TIM_TypeDef* TIMx,u8 Channel);
void PWMChangeValue(u16 duty , TIM_TypeDef* TIMx,u8 Channel);
	
#endif
