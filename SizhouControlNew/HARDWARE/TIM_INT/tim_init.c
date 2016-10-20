#include "tim_init.h"
#include "sys.h"
#include "sizhou_data_and_status.h"

extern QB_SZ_STATUS	g_qb_sz_status;


/**
  * @brief 	��ʼ��һ����ʱ���ж�
  * @param 	arr���趨�������Զ���װֵ 
						psc��Ԥ��Ƶ������
  * @retval None
  */
void QBTimItInit(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<11;	//TIM4ʱ��ʹ��    
 	TIM1->ARR=arr;  	//�趨�������Զ���װֵ 
	TIM1->PSC=psc;  	//Ԥ��Ƶ������
	TIM1->DIER|=1<<0;   //��������ж�				
	TIM1->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  MY_NVIC_Init(1,3,TIM1_UP_IRQn,2);//��ռ1�������ȼ�3����2									 
}

/**
  * @brief 	��ʱ���жϷ�����
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{ 		    		  			    
	if(TIM1->SR&0X0001)//����ж�;
	{
		g_qb_sz_status.control_flag++;						/*������Ƶı�־λ	*/
	}			
	TIM1->SR&=~(1<<0);//����жϱ�־λ 	    
}
