# ifndef _CONTROL_H
# define _CONTROL_H
# include "stm32f10x.h"
# include "pwm.h"
# include "delay.h"
# include "IMU_USART.h"
# include "usart.h"
typedef struct
{
	double P;
	double I;
	double D;
}PIDCoefficient;


typedef struct
{
	PIDCoefficient pitch;
	PIDCoefficient roll;
	PIDCoefficient yaw;
}ControlK;

/////////////////////////
//����
//////////////////////////
extern ControlK  ControlCopterK;//PID����ϵ��
extern ThreeAxis TargetAngle;//Ŀ����
extern int PowerBase;

/////////////////////////
//�������
//��ʱ������2s
/////////////////////////
void MotorUnlock(void);

////////////////////////
///�����������
//��ʱ������4s
///////////////////////
void MotorRangeAdjust(void);//�ϵ�ʱʹ��


//////////////////////////////////////
///��̬����������ʼ��
///
//////////////////////////////////////
void CopterAdjustInit(double pitch_p,double pitch_i,double pitch_d,double roll_p,double roll_i,double roll_d,double yaw_p,double yaw_i,double yaw_d);
	
//////////////////////////////////////
///��̬����
///
//////////////////////////////////////
void CopterAdjust(void);

#endif
