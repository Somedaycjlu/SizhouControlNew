#include "stm32f10x.h"
#include "hardware_conf.h"
#include "software_conf.h"
#include "delay.h"

QB_SZ_STATUS	g_qb_sz_status = {0};

int main()
{
	/*-------------------用来进行驱动测试的变量----------------------*/
//	s16 x_gyr, y_gyr, z_gyr;
//	s16 x_acc, y_acc, z_acc;
	/*-------------------用来进行驱动测试的变量----------------------*/
	
	delay_init();																	/*此处必须调用该初始化函数，			*/
																								/*否则delay函数无法使用						*/
	OLED_Init();																	/*OLED初始化											*/
	
	//MPU_Init();																		/*MPU6050初始化										*/
	
	QBPwmInit(9999,17);														/*四路pwm初始化，频率400Hz				*/
	
	QBTimItInit(39,7199);													/*初始化定时器1的中断4MS					*/
	
	QBSizhouStartUp();														/*四周启动的油门信号							*/
	
	QBNormalize(&g_qb_sz_status);									/*对角度值和角速度值进行归一化		*/
	
	//测试油门信号是否正常
	Moto_PWM_1 = 3300;				//1   //安全启动转速
	Moto_PWM_2 = 3300;				//4
	Moto_PWM_3 = 3300;				//2
	Moto_PWM_4 = 3300;				//3
	
	while(1)
	{
		QBMpu6050DataFilter(&g_qb_sz_status);
		if(g_qb_sz_status.control_flag >= 1)
		{
			g_qb_sz_status.control_flag = 0;
			QBSiZhouBaseControl(&g_qb_sz_status); 
		}
																 OLED_ShowString(40, 0, "Gyr:");	OLED_ShowString(80, 0, "Acc:");
		OLED_ShowString(0, 1, "x:"); OLED_ShowNum(40,1, g_qb_sz_status.gyr.X, 5); 	OLED_ShowNum(80,1, g_qb_sz_status.acc.X, 5);							//x
		OLED_ShowString(0, 2, "y:"); OLED_ShowNum(40,2, g_qb_sz_status.gyr.Y, 5); 	OLED_ShowNum(80,2, g_qb_sz_status.acc.Y, 5);							//y
		OLED_ShowString(0, 3, "z:"); OLED_ShowNum(40,3, g_qb_sz_status.gyr.Z, 5); 	OLED_ShowNum(80,3, g_qb_sz_status.acc.Z, 5);			
		OLED_ShowString(0, 4, "x_int:"); 	OLED_ShowNum(40,4, g_qb_sz_status.init_gyr.X, 5); OLED_ShowNum(80,4, g_qb_sz_status.init_acc.X, 5);
		OLED_ShowString(0, 5, "y_int:");  OLED_ShowNum(40,5, g_qb_sz_status.init_gyr.Y, 5); OLED_ShowNum(80,5, g_qb_sz_status.init_acc.Y, 5);
		OLED_ShowString(0, 6, "z_int:");	OLED_ShowNum(40,6, g_qb_sz_status.init_gyr.Z, 5); OLED_ShowNum(80,6, g_qb_sz_status.init_acc.Z, 5);
		
	}
}

