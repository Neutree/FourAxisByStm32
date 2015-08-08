#ifndef _IMU_USART_H
#define _IMU_USART_H
#include "stm32f10x.h"

typedef struct
{
	double pitch;
	double roll;
	double yaw;
}ThreeAxis,*ThreeAxis_p;


typedef struct
{
	u8 pitch;
	u8 roll;
	u8 yaw;
}Negate;

typedef struct
{
	ThreeAxis ACC;
	ThreeAxis GYRO;
	ThreeAxis ANGLE;
}IMUData;

extern double T;
extern IMUData IMUDataSolved;
extern Negate IsNegate;//���������Ƿ�ȡ������Ӧ����


void IMUInit(u8 IsNegate_pitch,u8 IsNegate_roll,u8 IsNegate_yaw);//��ʼ��
void DECODE_IMU_DATA(void);

#endif
