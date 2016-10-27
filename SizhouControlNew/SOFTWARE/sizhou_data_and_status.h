#ifndef SIZHOU_DATA_AND_STATUS_H
#define SIZHOU_DATA_AND_STATUS_H

#include "stm32f10x.h"			//此处包含主要是为了使用数据类型重用

typedef s8	FLAG;

typedef struct
{
	s16 X;
	s16 Y;
	s16 Z;
}DATA_ACC;

typedef struct
{
	s16 X;
	s16 Y;
	s16 Z;
}DATA_GYR;
	
typedef struct
{
	float Pitch;
	float Roll;
	float Yaw;
}Euler_Angle;


typedef struct
{
	DATA_ACC 	acc;
	DATA_GYR 	gyr;
	Euler_Angle euler;
	Euler_Angle init_euler;			//此处都不需要对该值进行归一化，提供的驱动程序已经归一化好了
	DATA_ACC 	init_acc;
	DATA_GYR 	init_gyr;
	FLAG		control_flag;
	
	
}QB_SZ_STATUS;

#endif
