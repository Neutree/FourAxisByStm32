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
extern Negate IsNegate;//各个方向是否取反，适应方向


void IMUInit(u8 IsNegate_pitch,u8 IsNegate_roll,u8 IsNegate_yaw);//初始化
void DECODE_IMU_DATA(void);

#endif
