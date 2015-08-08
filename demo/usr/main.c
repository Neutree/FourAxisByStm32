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
	
	IMUInit(1,0,0);//pitch���� roll yaw ������
	MotorRangeAdjust();//����ϵ�����У׼  ��ʱ������4s
	CopterAdjustInit(1.5,0,2,1.5,0,2,0,0,0);//PIDֵ��ʼ��
}

int main()
{
	init();
	while(1)
	{
		if(flag10ms==1)//10msһ��  100Hz
		{
			CopterAdjust();
			//MotorTimer->CCR1=4200;
		}
	}
}
