#include "IMU_USART.h"

double T;
IMUData IMUDataSolved;
Negate IsNegate;//各个方向是否取反，适应方向
u8 re_buff[11];
u8 flag[3]={0,0,0};

void DECODE_IMU_DATA()
{
//	u8 i=0;
	

//	if(re_buff[10]== (( (u16)re_buff[0] +re_buff[1]+re_buff[2]+re_buff[3]+re_buff[4]+re_buff[5]+re_buff[6]+re_buff[7]+re_buff[8]+re_buff[9]) % 256)  )
//	{
	if( re_buff[10] == (u8)(re_buff[0] +re_buff[1]+re_buff[2]+re_buff[3]+re_buff[4]+re_buff[5]+re_buff[6]+re_buff[7]+re_buff[8]+re_buff[9]) )
	{
//		printf("%d\t",sum);
//		for(i=0;i<11;++i)
//		{
//			printf("%d\t",re_buff[i]);
//		}
//		printf("\n");
//		printf("%d\t%d\n",re_buff[8],re_buff[9]);
		
		switch(re_buff[1])
		{
			case 0x51: //标识这个包是加速度包
					IMUDataSolved.ACC.roll = ((short)(re_buff[3]<<8 | re_buff[2]))/32768.0*16;      //X轴加速度
					IMUDataSolved.ACC.pitch = ((short)(re_buff[5]<<8 | re_buff[4]))/32768.0*16;      //Y轴加速度
					IMUDataSolved.ACC.yaw = ((short)(re_buff[7]<<8 | re_buff[6]))/32768.0*16;      //Z轴加速度
					T = ((short)(re_buff[9]<<8 | re_buff[8]))/340.0+36.25;      //温度
					flag[0]=1;
					break;
			 case 0x52: //标识这个包是角速度包
					IMUDataSolved.GYRO.roll = ((short)(re_buff[3]<<8| re_buff[2]))/32768.0*2000;      //X轴角速度
					IMUDataSolved.GYRO.pitch = ((short)(re_buff[5]<<8| re_buff[4]))/32768.0*2000;      //Y轴角速度
					IMUDataSolved.GYRO.yaw = ((short)(re_buff[7]<<8| re_buff[6]))/32768.0*2000;      //Z轴角速度
					T    = ((short)(re_buff[9]<<8| re_buff[8]))/340.0+36.25;      //温度
					flag[1]=1;
					break;
			 case 0x53: //标识这个包是角度包
					IMUDataSolved.ANGLE.roll = ((short)(re_buff[3]<<8| re_buff[2]))/32768.0*180;   //X轴滚转角（x 轴）
					IMUDataSolved.ANGLE.pitch = ((short)(re_buff[5]<<8| re_buff[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
					IMUDataSolved.ANGLE.yaw = ((short)(re_buff[7]<<8| re_buff[6]))/32768.0*180;   //Z轴偏航角（z 轴）
					T        = ((short)(re_buff[9]<<8| re_buff[8]))/340.0+36.25;   //温度
					flag[2]=1;
					break;
		}
		if(IsNegate.pitch==1)//被要求翻转
		{
			if(flag[0]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.ACC.pitch = - IMUDataSolved.ACC.pitch;
			}
			if(flag[1]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.GYRO.pitch = - IMUDataSolved.GYRO.pitch ;
			}
			if(flag[2]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.ANGLE.pitch = - IMUDataSolved.ANGLE.pitch;
			}
		}
		if(IsNegate.roll==1)
		{
			if(flag[0]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.ACC.roll = - IMUDataSolved.ACC.roll;
			}
			if(flag[1]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.GYRO.roll = - IMUDataSolved.GYRO.roll ;
			}
			if(flag[2]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.ANGLE.roll = - IMUDataSolved.ANGLE.roll;
			}
		}
		if(IsNegate.yaw==1)
		{
			if(flag[0]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.ACC.yaw = - IMUDataSolved.ACC.yaw;
			}
			if(flag[1]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.GYRO.yaw = - IMUDataSolved.GYRO.yaw ;
			}
			if(flag[2]==1)//新的数据已经准备好,防止连续两次取负同一组数据，会导致数据错误
			{
				IMUDataSolved.ANGLE.yaw = - IMUDataSolved.ANGLE.yaw;
			}
		}
		flag[0]=0;//清除数据已更新标志
		flag[1]=0;
		flag[2]=0;

//    	printf("%lf\t%lf\t%lf\t\n",IMUDataSolved.ANGLE.pitch,IMUDataSolved.ANGLE.roll,IMUDataSolved.ANGLE.yaw);        
	}
		
}
void IMUInit(u8 IsNegate_pitch,u8 IsNegate_roll,u8 IsNegate_yaw)
{
	if(IsNegate_pitch==1)
		IsNegate.pitch=1;
	else
		IsNegate.pitch=0;//俯仰不取反
	if(IsNegate_roll==1)
		IsNegate.roll=1;
	else
		IsNegate.roll=0;//横滚不取反
	if(IsNegate_yaw==1)
		IsNegate.yaw=1;
	else
		IsNegate.yaw=0;//航向不取反
}
