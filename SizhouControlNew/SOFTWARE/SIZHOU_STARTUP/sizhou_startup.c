#include "sizhou_startup.h"
#include "pwm.h"
#include "delay.h"


/**
  * @brief 	四轴起飞的油门信号
  * @param 	arr：设定计数器自动重装值 
						psc：预分频器设置
  * @retval None
  */
void QBSizhouStartUp(void)
{
	Moto_PWM_1=8000;							//油门最高点   80%
	Moto_PWM_2=8000;
	Moto_PWM_3=8000;
	Moto_PWM_4=8000;
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	Moto_PWM_1=3000;							//油门最低点  30%
	Moto_PWM_2=3000;
	Moto_PWM_3=3000;
	Moto_PWM_4=3000;
	delay_ms(1000);
	delay_ms(1000);
	Moto_PWM_1=3000;	 						//准备起飞    30%
	Moto_PWM_2=3000;
	Moto_PWM_3=3000;
	Moto_PWM_4=3000;
	delay_ms(1000);
}
