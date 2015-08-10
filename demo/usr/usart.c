#include "usart.h"

void Usart_Configuration(void)			//����Usart1 Tx->PA2 Rx->PA3
{
	 GPIO_InitTypeDef GPIO_InitStructure; //GPIO�⺯���ṹ��
	 USART_InitTypeDef USART_InitStructure;//USART�⺯���ṹ��
	 USART_ClockInitTypeDef USART_ClockInitStructure;
	 //ʹ�ܴ���1��GPIOA��AFIO����
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1,ENABLE);

	 /* Configure USART1 Tx (PA9) as alternate function push-pull */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//PA9ʱ���ٶ�50MHz
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 /* Configure USART1 Rx (PA10) as input floating */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	 USART_InitStructure.USART_BaudRate =115200; //������115200
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8λ����
	 USART_InitStructure.USART_StopBits = USART_StopBits_1; //1��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No; //��żʧ��
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���͡�����ʹ��
	
	 USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	 USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;//����ʱ��Ϊ�͵�ƽ
	 USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;//ʱ�ӵڶ������ؽ������ݲ���
	 USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;//���һλ���ݵ�ʱ�����岻��SCLK���

	 //ʹ�ܴ���1�����ж�
	 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 

	 USART_ClockInit(USART1, &USART_ClockInitStructure);
	 USART_Init(USART1, &USART_InitStructure);	//��ʼ���ṹ��
	 USART_Cmd(USART1, ENABLE); //ʹ�ܴ���1
	 USART_ClearFlag(USART1,USART_FLAG_TC);//���������ɱ�־����Ȼ��ʱ���ܻ��е�һ���ַ����Ͳ���ȥ�����
}
void Usart_NVIC_Configuration(void)
{
	 NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/******************ע�ᴮ��1�жϷ�����************************/
   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//���ô����ж�
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//ռ��ʽ���ȼ�����Ϊ0
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�����Ϊ0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�жϿ���
   NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
}
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
/***************************START*********************/
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	USART1->DR = (u8) ch;      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	return ch;
}
#endif 
/***************************END*********************/

void USART1_Putc(uint8_t data)			//����Usart1����һ��8λ����
{
    USART1->DR = (uint8_t)data; //Ҫ���͵��ַ������������ݼĴ���  
	while((USART1->SR&0X40)==0); //�ȴ��������  
}
void USART1_Puts(uint8_t * buffer)			//����Usart1����һ���ַ���
{
    while(*buffer)
    {
        USART1->DR= *buffer++;
		while((USART1->SR&0X40)==0);//�ȴ��������  
    }
}
void USART1_Send_Enter(void)//���ô���1����һ���з�
{
	USART1_Putc(0x0d);
	USART1_Putc(0x0a);
}


void Usart2_Configuration(void)			//����Usart2 Tx->PA2 Rx->PA3
{
	 GPIO_InitTypeDef GPIO_InitStructure; //GPIO�⺯���ṹ��
	 USART_InitTypeDef USART_InitStructure;//USART�⺯���ṹ��
	 USART_ClockInitTypeDef USART_ClockInitStructure;
	 //ʹ�ܴ���2��GPIOA��AFIO����
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	 /* Configure USART1 Tx (PA9) as alternate function push-pull */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//PA9ʱ���ٶ�50MHz
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 /* Configure USART1 Rx (PA10) as input floating */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	 USART_InitStructure.USART_BaudRate =115200; //������115200
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8λ����
	 USART_InitStructure.USART_StopBits = USART_StopBits_1; //1��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No; //��żʧ��
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���͡�����ʹ��
	
	 USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	 USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;//����ʱ��Ϊ�͵�ƽ
	 USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;//ʱ�ӵڶ������ؽ������ݲ���
	 USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;//���һλ���ݵ�ʱ�����岻��SCLK���

	 //ʹ�ܴ���1�����ж�
	 USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 

	 USART_ClockInit(USART2, &USART_ClockInitStructure);
	 USART_Init(USART2, &USART_InitStructure);	//��ʼ���ṹ��
	 USART_Cmd(USART2, ENABLE); //ʹ�ܴ���1
	 USART_ClearFlag(USART2,USART_FLAG_TC);//���������ɱ�־����Ȼ��ʱ���ܻ��е�һ���ַ����Ͳ���ȥ�����
}
void Usart2_NVIC_Configuration(void)
{
	 NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/******************ע�ᴮ��1�жϷ�����************************/
   NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//���ô����ж�
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//ռ��ʽ���ȼ�����Ϊ0
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�����Ϊ0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�жϿ���
   NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
}


/******************����1�жϷ�����*******************************/
void USART1_IRQHandler(void)
{
	u8 data=0;
   if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
   {
		 data=USART_ReceiveData(USART1);
		 if(data=='1')
		 {
			TIM4->CCR1+=10;
			 printf("PowerBase:%10d\n",TIM4->CCR1);
		 }
		else if(data=='2')
		{
			TIM4->CCR1-=10;
			printf("PowerBase:%10d\n",TIM4->CCR1);
		}
		else if(data=='3')
		{
			ControlCopterK.pitch.P+=0.1;
			printf("P:%10.2lf\n",ControlCopterK.pitch.P);
		}
		else if(data=='4')
		{
			ControlCopterK.pitch.P-=0.1;
			printf("P:%10.2lf\n",ControlCopterK.pitch.P);
		}
		else if(data=='5')
		{
			ControlCopterK.pitch.I+=0.01;
			printf("I:%10.2lf\n",ControlCopterK.pitch.I);
		}
		else if(data=='6')
		{
			ControlCopterK.pitch.I-=0.01;
			printf("I:%10.2lf\n",ControlCopterK.pitch.I);
		}
		else if(data=='7')
		{
			ControlCopterK.pitch.D+=0.1;
			printf("D:%10.2lf\n",ControlCopterK.pitch.D);
		}
		else if(data=='8')
		{
			ControlCopterK.pitch.D-=0.1;
			printf("D:%10.2lf\n",ControlCopterK.pitch.D);
		}
		USART_SendData(USART1,data);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
	 }
}


/******************����2�жϷ�����*******************************/
u8 Recieved_Count2=0;
static u8 data_buffer2[11];
u8 Data_Recieved_Flag=0;
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
   {
		 data_buffer2[Recieved_Count2]=USART_ReceiveData(USART2);//�����ݷŵ���������data_buffer2[]��
		 if(Recieved_Count2==0 && data_buffer2[0]!=0x55)//��ͷ�����ݲ���0x55,����
			 return;
		  ++Recieved_Count2;//������������+1
		 if(Recieved_Count2==11)
		 {
			 memcpy(re_buff,data_buffer2,11);
			 Recieved_Count2=0;
			 Data_Recieved_Flag=1;
//			 printf("#######%d\t%d\t%d\t%d\t########\n",data_buffer2[0],data_buffer2[1],data_buffer2[2],data_buffer2[3]);
//			 printf("#######%d\t%d\t%d\t%d\t########\n",re_buff[0],re_buff[1],re_buff[2],re_buff[3]);
		 }
	 }
}

