#ifndef DATA_DEAL_H_
#define DATA_DEAL_H_

#include "sizhou_data_and_status.h"

void QBNormalize(QB_SZ_STATUS *qb_sz_status);
void QBMpu6050DataFilter(QB_SZ_STATUS *qb_sz_status);
void QBEulerPackge(float *pitch, float *roll, float *yaw );	
#endif
