#include "sizhou_control.h"
#include "pwm.h"
#include "sizhou_data_and_status.h"

#include "oled.h"
/**
  * @brief 	四轴姿态的基本控制
  * @param 	qb_sz_status：指向用来记录四轴数据标志的结构体指针
  * @retval None
  */
void QBSiZhouBaseControl(QB_SZ_STATUS *qb_sz_status) 
{
	static u8 count = 0;
	
			u8 i = 0;
	
			u16 pwm1_mid_sum = 0, pwm2_mid_sum = 0, pwm3_mid_sum = 0, pwm4_mid_sum = 0;
	
			u16 pwm1_mid_x   = 0, pwm2_mid_x   = 0, pwm3_mid_x   = 0, pwm4_mid_x   = 0;
	
			u16 pwm1_mid_y   = 0, pwm2_mid_y   = 0, pwm3_mid_y   = 0, pwm4_mid_y   = 0;
	
			u16 pwm1_mid_z   = 0, pwm2_mid_z   = 0, pwm3_mid_z   = 0, pwm4_mid_z   = 0;
			
				
	
	static float err_x 			  =  0, err_y 		      =  0,  err_z 		       =  0;
	
	static float pre_err_x 		  =  0, pre_err_y 	      =  0,  pre_err_z 	       =  0;
	
	static float err_x_integral[5]= {0},err_y_integral[5] = {0}, err_z_integral[5] = {0};
	
	/*由于此处只需要对每次的误差进行积累，而不需要对每次的积累总之进行积累，所以不定位静态*/
		   float err_x_sum        =  0,  err_y_sum 		  =  0,   err_z_sum        =  0;
	
	pre_err_x = err_x;
	pre_err_y = err_y;
	pre_err_z = err_z;
	
	err_x = qb_sz_status->euler.Pitch;
	err_y = qb_sz_status->euler.Roll;
	err_z = qb_sz_status->euler.Yaw;
	
	err_x_integral[count++] = err_x;
	err_y_integral[count++] = err_y;
	
	if (count >= 5)
		count = 0;
	
	for (i = 0; i < 5; i++)
	{
		err_x_sum += err_x_integral[i];
		err_y_sum += err_y_integral[i];
	}
	
	if (err_x_sum > 20)			err_x_sum = 20;
	else if (err_x_sum < -20) 	err_x_sum = -20;
	if (err_y_sum > 20)			err_y_sum = 20;
	else if (err_y_sum < -20) 	err_y_sum = -20;
	
	pwm1_mid_x =  (16 * err_x + 2 * err_x_sum + 700 * (err_x - pre_err_x));
	pwm2_mid_x =  (16 * err_x + 2 * err_x_sum + 700 * (err_x - pre_err_x));
	pwm3_mid_x = -(16 * err_x + 2 * err_x_sum + 700 * (err_x - pre_err_x));
	pwm4_mid_x = -(16 * err_x + 2 * err_x_sum + 700 * (err_x - pre_err_x));
	
	pwm1_mid_y =  (16 * err_y + 2 * err_y_sum + 700 * (err_y - pre_err_y));
	pwm2_mid_y = -(16 * err_y + 2 * err_y_sum + 700 * (err_y - pre_err_y));
	pwm3_mid_y = -(16 * err_y + 2 * err_y_sum + 700 * (err_y - pre_err_y));
	pwm4_mid_y =  (16 * err_y + 2 * err_y_sum + 700 * (err_y - pre_err_y));
	
	pwm1_mid_sum = 4750 + pwm1_mid_x + pwm1_mid_y;
	pwm2_mid_sum = 4750 + pwm2_mid_x + pwm2_mid_y;
	pwm3_mid_sum = 4750 + pwm3_mid_x + pwm3_mid_y;
	pwm4_mid_sum = 4750 + pwm4_mid_x + pwm4_mid_y;
	
	if (pwm1_mid_sum > 7000)	pwm1_mid_sum = 7000;
	if (pwm2_mid_sum > 7000)	pwm2_mid_sum = 7000;
	if (pwm3_mid_sum > 7000)	pwm3_mid_sum = 7000;
	if (pwm4_mid_sum > 7000)	pwm4_mid_sum = 7000;

	Moto_PWM_1 = pwm1_mid_sum;
	Moto_PWM_2 = pwm2_mid_sum;
	Moto_PWM_3 = pwm3_mid_sum;
	Moto_PWM_4 = pwm4_mid_sum;
}

