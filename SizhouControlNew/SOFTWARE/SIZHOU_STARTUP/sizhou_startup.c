#include "sizhou_startup.h"
#include "pwm.h"
#include "delay.h"


/**
  * @brief 	������ɵ������ź�
  * @param 	arr���趨�������Զ���װֵ 
						psc��Ԥ��Ƶ������
  * @retval None
  */
void QBSizhouStartUp(void)
{
	Moto_PWM_1=8000;							//������ߵ�   80%
	Moto_PWM_2=8000;
	Moto_PWM_3=8000;
	Moto_PWM_4=8000;
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	Moto_PWM_1=3000;							//������͵�  30%
	Moto_PWM_2=3000;
	Moto_PWM_3=3000;
	Moto_PWM_4=3000;
	delay_ms(1000);
	delay_ms(1000);
	Moto_PWM_1=3000;	 						//׼�����    30%
	Moto_PWM_2=3000;
	Moto_PWM_3=3000;
	Moto_PWM_4=3000;
	delay_ms(1000);
}
