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
	pwm1_mid = 3500 + (s16)(0.06 * (double)qb_sz_status->gyr.X) - \
	(s16)(0.3 * (double)(qb_sz_status->acc.X)); 
	if (pwm1_mid > 4500) pwm1_mid = 4500; 
	else if (pwm1_mid < 2000) pwm1_mid = 2000;
	
	pwm2_mid = 3500 + (s16)(0.06 * (double)qb_sz_status->gyr.X) - \
	(s16)(0.3 * (double)(qb_sz_status->acc.X)); 
	if (pwm2_mid > 4500) pwm2_mid = 4500; 
	else if (pwm2_mid < 2000) pwm2_mid = 2000;
	
	pwm3_mid = 3500 - (s16)(0.06 * (double)qb_sz_status->gyr.X) + \
	(s16)(0.3 * (double)(qb_sz_status->acc.X)); 
	if (pwm3_mid > 4500) pwm3_mid = 4500; 
	else if (pwm3_mid < 2000) pwm3_mid = 2000;
	
	pwm4_mid = 3500 - (s16)(0.06 * (double)qb_sz_status->gyr.X) + \
	(s16)(0.3 * (double)(qb_sz_status->acc.X)); 
	if (pwm4_mid > 4500) pwm4_mid = 4500; 
	else if (pwm4_mid < 2000) pwm4_mid = 2000;

	Moto_PWM_1 = pwm1_mid;
	Moto_PWM_2 = pwm2_mid;
	Moto_PWM_3 = pwm3_mid;
	Moto_PWM_4 = pwm4_mid;
}
