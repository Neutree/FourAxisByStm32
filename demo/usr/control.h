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
//变量
//////////////////////////
extern ControlK  ControlCopterK;//PID控制系数
extern ThreeAxis TargetAngle;//目标量
extern int PowerBase;

/////////////////////////
//电调解锁
//用时：大于2s
/////////////////////////
void MotorUnlock(void);

////////////////////////
///最大油门设置
//用时：大于4s
///////////////////////
void MotorRangeAdjust(void);//上电时使用


//////////////////////////////////////
///姿态矫正变量初始化
///
//////////////////////////////////////
void CopterAdjustInit(double pitch_p,double pitch_i,double pitch_d,double roll_p,double roll_i,double roll_d,double yaw_p,double yaw_i,double yaw_d);
	
//////////////////////////////////////
///姿态矫正
///
//////////////////////////////////////
void CopterAdjust(void);

#endif
