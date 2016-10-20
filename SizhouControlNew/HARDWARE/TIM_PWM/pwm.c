#include "pwm.h"



/**
  * @brief 	��ʼ��TIM3��PWMģ��
  * @param 	arr���趨�������Զ���װֵ 
						psc��Ԥ��Ƶ������
  * @retval None
  */
static void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	
	RCC->APB1ENR|=1<<1;					//TIM3ʱ��ʹ�� 
	
	RCC->APB2ENR|=1<<2;    			//ʹ��PORTAʱ��	 

	GPIOA->CRL&=0X00FFFFFF;			//PA6,7���֮ǰ������
	GPIOA->CRL|=0XBB000000;			//���ù������ 

	
	TIM3->ARR=arr;							//�趨�������Զ���װֵ 
	TIM3->PSC=psc;							//Ԥ��Ƶ������
  
	TIM3->CCMR1|=7<<4;  				//CH1 PWM2ģʽ		
	TIM3->CCMR1|=7<<12;	

	
	TIM3->CCMR1|=1<<3; 					//CH1Ԥװ��ʹ��	 
	TIM3->CCMR1|=1<<11;

	
 	TIM3->CCER|=3<<0;   				//OC1 ���ʹ��	   
	TIM3->CCER|=3<<4;

	
	
	TIM3->CR1 = 0x0080;   			//ARPEʹ�� 
	TIM3->CR1|= 0x01;    				//ʹ�ܶ�ʱ��3										  
}  

/**
  * @brief 	��ʼ��TIM4��PWMģ��
  * @param 	arr���趨�������Զ���װֵ 
						psc��Ԥ��Ƶ������
  * @retval None
  */
static void TIM4_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1<<2;				//TIM4ʱ��ʹ�� 
	RCC->APB2ENR |= 1<<3;    		//ʹ��PORTBʱ��	 
	GPIOB->CRH &= 0XFFFFFF00;		//PB8,9���֮ǰ������
	GPIOB->CRH |= 0X000000BB;		//���ù������ 

	TIM4->ARR=arr;							//�趨�������Զ���װֵ 
	TIM4->PSC=psc;							//Ԥ��Ƶ������

	TIM4->CCMR2|=7<<4;  	
	TIM4->CCMR2|=7<<12;	

	TIM4->CCMR2|=1<<3; 		
	TIM4->CCMR2|=1<<11;

	TIM4->CCER|=3<<8;
	TIM4->CCER|=3<<12;


	TIM4->CR1=0x0080;   				//ARPEʹ�� 
	TIM4->CR1|=0x01;    				//ʹ�ܶ�ʱ��3	
}

/**
  * @brief 	��ʼ����·PWMģ��
  * @param 	arr���趨�������Զ���װֵ 
						psc��Ԥ��Ƶ������
  * @retval None
  */
void QBPwmInit(u16 arr,u16 psc)
{
	TIM3_PWM_Init(arr,psc);
	TIM4_PWM_Init(arr,psc);
}
