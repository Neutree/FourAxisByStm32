#include "pwm.h"


void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);//复用功能重映像
	//定时器初始化  输出pwm频率为400HZ
	TIM_TimeBaseStruct.TIM_Period=59999;
	TIM_TimeBaseStruct.TIM_Prescaler=2;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_RepetitionCounter=0;

	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//pwm初始化
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;  //初始占空比为	TIM_SetCompare2(TIM4,80); TIM4->CCR2=80; 均可设置
	
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);//通道二初始化
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//设置预装值
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);//通道二初始化
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);//设置预装值
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);//通道二初始化
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);//设置预装值
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);//通道二初始化
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);//设置预装值
	//TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM4,ENABLE);//定时器4使能
	
}
void PWMConfig()
{
	TIM4_Configuration();
}

void PWMChangeDuty(double duty , TIM_TypeDef* TIMx,u8 Channel)
{
	if(Channel==1)
		TIMx->CCR1=(TIMx->ARR+1)*duty;
	else if(Channel==2)
		TIMx->CCR2=(TIMx->ARR+1)*duty;
	else if(Channel==3)
		TIMx->CCR3=(TIMx->ARR+1)*duty;
	else if(Channel==4)
		TIMx->CCR4=(TIMx->ARR+1)*duty;
}
void PWMChangeValue(u16 Value , TIM_TypeDef* TIMx,u8 Channel)
{
	if(Channel==1)
		TIMx->CCR1=Value;
	else if(Channel==2)
		TIMx->CCR2=Value;
	else if(Channel==3)
		TIMx->CCR3=Value;
	else if(Channel==4)
		TIMx->CCR4=Value;
}
