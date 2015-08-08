#include "IMU_USART.h"

double T;
IMUData IMUDataSolved;
Negate IsNegate;//���������Ƿ�ȡ������Ӧ����
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
			case 0x51: //��ʶ������Ǽ��ٶȰ�
					IMUDataSolved.ACC.roll = ((short)(re_buff[3]<<8 | re_buff[2]))/32768.0*16;      //X����ٶ�
					IMUDataSolved.ACC.pitch = ((short)(re_buff[5]<<8 | re_buff[4]))/32768.0*16;      //Y����ٶ�
					IMUDataSolved.ACC.yaw = ((short)(re_buff[7]<<8 | re_buff[6]))/32768.0*16;      //Z����ٶ�
					T = ((short)(re_buff[9]<<8 | re_buff[8]))/340.0+36.25;      //�¶�
					flag[0]=1;
					break;
			 case 0x52: //��ʶ������ǽ��ٶȰ�
					IMUDataSolved.GYRO.roll = ((short)(re_buff[3]<<8| re_buff[2]))/32768.0*2000;      //X����ٶ�
					IMUDataSolved.GYRO.pitch = ((short)(re_buff[5]<<8| re_buff[4]))/32768.0*2000;      //Y����ٶ�
					IMUDataSolved.GYRO.yaw = ((short)(re_buff[7]<<8| re_buff[6]))/32768.0*2000;      //Z����ٶ�
					T    = ((short)(re_buff[9]<<8| re_buff[8]))/340.0+36.25;      //�¶�
					flag[1]=1;
					break;
			 case 0x53: //��ʶ������ǽǶȰ�
					IMUDataSolved.ANGLE.roll = ((short)(re_buff[3]<<8| re_buff[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
					IMUDataSolved.ANGLE.pitch = ((short)(re_buff[5]<<8| re_buff[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
					IMUDataSolved.ANGLE.yaw = ((short)(re_buff[7]<<8| re_buff[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
					T        = ((short)(re_buff[9]<<8| re_buff[8]))/340.0+36.25;   //�¶�
					flag[2]=1;
					break;
		}
		if(IsNegate.pitch==1)//��Ҫ��ת
		{
			if(flag[0]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.ACC.pitch = - IMUDataSolved.ACC.pitch;
			}
			if(flag[1]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.GYRO.pitch = - IMUDataSolved.GYRO.pitch ;
			}
			if(flag[2]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.ANGLE.pitch = - IMUDataSolved.ANGLE.pitch;
			}
		}
		if(IsNegate.roll==1)
		{
			if(flag[0]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.ACC.roll = - IMUDataSolved.ACC.roll;
			}
			if(flag[1]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.GYRO.roll = - IMUDataSolved.GYRO.roll ;
			}
			if(flag[2]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.ANGLE.roll = - IMUDataSolved.ANGLE.roll;
			}
		}
		if(IsNegate.yaw==1)
		{
			if(flag[0]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.ACC.yaw = - IMUDataSolved.ACC.yaw;
			}
			if(flag[1]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.GYRO.yaw = - IMUDataSolved.GYRO.yaw ;
			}
			if(flag[2]==1)//�µ������Ѿ�׼����,��ֹ��������ȡ��ͬһ�����ݣ��ᵼ�����ݴ���
			{
				IMUDataSolved.ANGLE.yaw = - IMUDataSolved.ANGLE.yaw;
			}
		}
		flag[0]=0;//��������Ѹ��±�־
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
		IsNegate.pitch=0;//������ȡ��
	if(IsNegate_roll==1)
		IsNegate.roll=1;
	else
		IsNegate.roll=0;//�����ȡ��
	if(IsNegate_yaw==1)
		IsNegate.yaw=1;
	else
		IsNegate.yaw=0;//����ȡ��
}
