# include "stm32f10x.h"
# include "pwm.h"
# include "usart.h"
# include "delay.h"
# include "time.h"
# include "control.h"
void init()
{
	SystemInit();
	Usart_Configuration();
	Usart_NVIC_Configuration();
	Usart2_Configuration();
	Usart2_NVIC_Configuration();
	TIM3_Configuration();
	PWMConfig();
	
	IMUInit(1,0,0);//pitch反向 roll yaw 不反向
 	MotorRangeAdjust();//电机上电启动校准  用时：大于4s
	CopterAdjustInit(6.1,0.15,0.8,0,0,0,0,0,0);//PID值初始化
}

int main()
{
	init();
	while(1)
	{
		if(flag10ms==1)//10ms一次  100Hz
		{
			CopterAdjust();
			flag10ms=0;
			//MotorTimer->CCR1=4200;
		}
	}
}
