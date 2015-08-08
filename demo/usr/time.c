#include "time.h"
//变量
/////////////////////////////
u16 timeCount_10ms=0;
u8 flag10ms=0;

////////////////////////////
/////定时器配置
////////////////////////////
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//10ms更新中断产生一次
	TIM_TimeBaseStruct.TIM_Period=9999;//溢出数大小
	TIM_TimeBaseStruct.TIM_Prescaler=71;//预分频
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);	 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}


//////////////////////////////////////////
//////TIM3中断处理函数
//////////////////////////////////////////
void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清中断标志
	flag10ms=1;
	++timeCount_10ms;	
	
}

