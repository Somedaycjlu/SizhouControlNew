#ifndef TIME3_PWM_H_
#define TIME3_PWM_H_

#include "stm32f10x.h"

#define Moto_PWM_1 TIM3->CCR1 		
#define Moto_PWM_2 TIM4->CCR3    
#define Moto_PWM_3 TIM4->CCR4 		
#define Moto_PWM_4 TIM3->CCR2 		

void QBPwmInit(u16 arr,u16 psc);

#endif

