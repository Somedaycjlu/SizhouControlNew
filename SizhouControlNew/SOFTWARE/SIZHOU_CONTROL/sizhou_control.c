#include "sizhou_control.h"
#include "pwm.h"
#include "sizhou_data_and_status.h"

/**
  * @brief 	四轴姿态的基本控制
  * @param 	qb_sz_status：指向用来记录四轴数据标志的结构体指针
  * @retval None
  */
void QBSiZhouBaseControl(QB_SZ_STATUS *qb_sz_status) 
{
	
	u16 pwm1_mid = 0, pwm2_mid = 0, pwm3_mid = 0, pwm4_mid = 0;
	float err_x = 0, err_y = 0, err_z = 0;
	float pre_err_x = 0, pre_err_y = 0, pre_err_z = 0;
	
	pre_err_x = err_x;
	pre_err_y = err_y;
	pre_err_z = err_z;
	
	err_x = qb_sz_status->euler.Pitch;
	err_y = qb_sz_status->euler.Roll;
	err_z = qb_sz_status->euler.Yaw;
	
	pwm1_mid = 3500 + (5 * err_x + 10 * (err_x - pre_err_x));
	pwm2_mid = 3500 + (5 * err_x + 10 * (err_x - pre_err_x));
	pwm3_mid = 3500 - (5 * err_x + 10 * (err_x - pre_err_x));
	pwm4_mid = 3500 - (5 * err_x + 10 * (err_x - pre_err_x));
	

	

	Moto_PWM_1 = pwm1_mid;
	Moto_PWM_2 = pwm2_mid;
	Moto_PWM_3 = pwm3_mid;
	Moto_PWM_4 = pwm4_mid;
}
