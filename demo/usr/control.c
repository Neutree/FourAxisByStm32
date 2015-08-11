#include "control.h"

//////////////////////////////////////
////变量
/////////////////////////////////////
ControlK  ControlCopterK;//PID控制系数
ThreeAxis TargetAngle;//目标量 角度
int PowerBase=35000;

/////////////////////////
//电调解锁
//用时：大于2s
/////////////////////////
void MotorUnlock()
{
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,1);
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,2);
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,3);
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,4);
	delay_s(2);
}
////////////////////////
///最大油门设置
//用时：大于5s
///////////////////////
void MotorRangeAdjust()//上电时使用
{
	//设置电机输出占空比，  值：2.0/MotorPWMT 代表最大，MotorPWMT为PWM波输出周期，定义在pwm.h中， 
	//电调输入识别一个周期内高电平持续的时间，区间为1ms~2ms,1ms为最小值，2ms为最大值，所以占空比为高电平时间除以周期
	PWMChangeDuty(2.0/MotorPWMT,MotorTimer,1);
	PWMChangeDuty(2.0/MotorPWMT,MotorTimer,2);
	PWMChangeDuty(2.0/MotorPWMT,MotorTimer,3);
	PWMChangeDuty(2.0/MotorPWMT,MotorTimer,4);
	delay_s(3);//等待2秒，发出beep  beep ，然后等待一秒拉低，设置完成发出beep---- beep-beep-beep- 123
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,1);
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,2);
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,3);
	PWMChangeDuty(1.0/MotorPWMT,MotorTimer,4);
	delay_s(2);
}
//////////////////////////////////////
///姿态矫正变量初始化
///
//////////////////////////////////////
void CopterAdjustInit(double pitch_p,double pitch_i,double pitch_d,double roll_p,double roll_i,double roll_d,double yaw_p,double yaw_i,double yaw_d)
{
	ControlCopterK.pitch.P=pitch_p;
	ControlCopterK.pitch.I=pitch_i;
	ControlCopterK.pitch.D=pitch_d;
	ControlCopterK.roll.P=roll_p;
	ControlCopterK.roll.I=roll_i;
	ControlCopterK.roll.D=roll_d;
	ControlCopterK.yaw.P=yaw_p;
	ControlCopterK.yaw.I=yaw_i;
	ControlCopterK.yaw.D=yaw_d;
	TargetAngle.pitch=0;
	TargetAngle.roll=0;
	TargetAngle.yaw=0;
}



//////////////////////////////////////
///姿态矫正
///
//////////////////////////////////////
ThreeAxis DeviationSumAngle;//角度误差累积
//角度误差
ThreeAxis DeviationAngle;
//角速度误差
ThreeAxis DeviationGYRO;
//输出量
ThreeAxis PowerOut;
void CopterAdjust()
{
	DECODE_IMU_DATA();//数据融合、处理
	//与目标值的误差计算
	
		//角度误差（比例项、积分项单次数据）
	DeviationAngle.pitch = TargetAngle.pitch - IMUDataSolved.ANGLE.pitch;
	DeviationAngle.roll  = TargetAngle.roll - IMUDataSolved.ANGLE.roll;
	DeviationAngle.yaw   = TargetAngle.yaw - IMUDataSolved.ANGLE.yaw;
	
	
		//角度误差累计（积分项）
	DeviationSumAngle.pitch += DeviationAngle.pitch;
	DeviationSumAngle.roll  += DeviationAngle.roll;
	DeviationSumAngle.yaw   += DeviationAngle.yaw;
			//积分限幅
	if(DeviationSumAngle.pitch>500)
		DeviationSumAngle.pitch=500;
	else if(DeviationSumAngle.pitch<-500)
		DeviationSumAngle.pitch=-500;
	if(DeviationSumAngle.roll>500)
		DeviationSumAngle.roll=500;
	else if(DeviationSumAngle.roll<-500)
		DeviationSumAngle.roll=-500;
	if(DeviationSumAngle.yaw>500)
		DeviationSumAngle.yaw=500;
	else if(DeviationSumAngle.yaw<-500)
		DeviationSumAngle.yaw=-500;
	
	
		//角速度误差（微分项）
	DeviationGYRO.pitch = 0 - IMUDataSolved.GYRO.pitch;
	DeviationGYRO.roll  = 0 - IMUDataSolved.GYRO.roll;
	DeviationGYRO.yaw   = 0 - IMUDataSolved.GYRO.yaw;
	
	PowerOut.pitch = ControlCopterK.pitch.P * DeviationAngle.pitch + ControlCopterK.pitch.I*DeviationSumAngle.pitch  +  ControlCopterK.pitch.D*DeviationGYRO.pitch;
	PowerOut.roll  = ControlCopterK.roll.P * DeviationAngle.roll   + ControlCopterK.roll.I*DeviationSumAngle.roll    +  ControlCopterK.roll.D*DeviationGYRO.roll;
	PowerOut.yaw   = ControlCopterK.yaw.P * DeviationAngle.yaw     + ControlCopterK.yaw.I*DeviationSumAngle.yaw      +  ControlCopterK.yaw.D*DeviationGYRO.yaw;
	//电机输出值
	PWMChangeValue(PowerBase+PowerOut.pitch+PowerOut.roll-PowerOut.yaw,MotorTimer,1);
	PWMChangeValue(PowerBase-PowerOut.pitch+PowerOut.roll+PowerOut.yaw,MotorTimer,2);
	PWMChangeValue(PowerBase-PowerOut.pitch-PowerOut.roll-PowerOut.yaw,MotorTimer,3);
	PWMChangeValue(PowerBase+PowerOut.pitch-PowerOut.roll+PowerOut.yaw,MotorTimer,4);
//	printf("%10.2lf\n",IMUDataSolved.ANGLE.pitch);
//	delay_ms(200);
}

