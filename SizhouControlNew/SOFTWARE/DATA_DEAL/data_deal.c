#include "data_deal.h"
#include "sizhou_data_and_status.h"
#include "mpu6050.h"

/**
  * @brief 	�Դ������ɼ�������ֵ�����˲�
  * @param 	qb_sz_status��ָ��������¼�������ݱ�־�Ľṹ��ָ��
  * @retval None
  */
void QBMpu6050DataFilter(QB_SZ_STATUS *qb_sz_status)
{
	u8 i = 0;
	
	s16 gyr_x_read, gyr_y_read, gyr_z_read;							/*�Ƕȶ���ֵ					*/
	s16 acc_x_read, acc_y_read, acc_z_read;
	
	s32 gyr_x_mid = 0, gyr_y_mid = 0, gyr_z_mid = 0;		/*���ٶȶ���ֵ				*/
	s32 acc_x_mid = 0, acc_y_mid = 0, acc_z_mid = 0;
	
	s16 gyr_x_filter, gyr_y_filter, gyr_z_filter;
	s16 acc_x_filter, acc_y_filter, acc_z_filter;
	

	
	for (i = 0; i < 10; i++)
	{
//		MPU_Get_Gyroscope(&gyr_x_read, &gyr_y_read, &gyr_z_read);				/*���ؽǶ�ֵ����������	*/	
//																									
//		MPU_Get_Accelerometer(&acc_x_read, &acc_y_read, &acc_z_read);		/*���ؽ��ٶ�ֵ����������*/
		
		gyr_x_mid += gyr_x_read;																				/*�����ۼӣ��˲�				*/
		gyr_y_mid += gyr_y_read;
		gyr_z_mid += gyr_z_read;
		acc_x_mid += acc_x_read;
		acc_y_mid += acc_y_read;
		acc_z_mid += acc_z_read;
	}
	
	gyr_x_filter = gyr_x_mid / 10;												/*��ֵ�˲�							*/
	gyr_y_filter = gyr_y_mid / 10;
	gyr_z_filter= gyr_z_mid / 10;
	
	acc_x_filter = acc_x_mid / 10;
	acc_y_filter = acc_y_mid / 10;
	acc_z_filter = acc_z_mid / 10;
	
	qb_sz_status->gyr.X = gyr_x_filter;
	qb_sz_status->gyr.Y = gyr_y_filter;
	qb_sz_status->gyr.Z = gyr_z_filter;
	
	qb_sz_status->acc.X = acc_x_filter;
	qb_sz_status->acc.Y = acc_y_filter;
	qb_sz_status->acc.Z = acc_z_filter;
	
	qb_sz_status->gyr.X = qb_sz_status->gyr.X - qb_sz_status->init_gyr.X;
	qb_sz_status->acc.X = qb_sz_status->acc.X - qb_sz_status->init_acc.X;
	
//	acc.err_x = acc.X - Acc_X_Init;
	
//	gyr.X=gyr.X-error_g_x+0.5;
//	gyr.Y=gyr.Y-error_g_y+0.5;
//	gyr.Z=gyr.Z-error_g_z+0.5;
//	acc.X-=error_a_x;
//	acc.Y-=error_a_y;
//	acc.Z-=error_a_z;
	 
//	IMU_Prepare();
//	sensfusion6_update(gyr_wf.X,gyr_wf.Y,gyr_wf.Z,acc_wf.X,acc_wf.Y,acc_wf.Z);
}


void QBMpu6050DataInit(QB_SZ_STATUS *qb_sz_status)
{
	
}

/**
  * @brief 	�Դ������ɼ�������ֵ���й�һ��
  * @param 	qb_sz_status��ָ��������¼�������ݱ�־�Ľṹ��ָ��
  * @retval None
  */
void QBNormalize(QB_SZ_STATUS *qb_sz_status)
{
	u8 i = 0;
	
	s16 gyr_x_read, gyr_y_read, gyr_z_read;							/*�Ƕȶ���ֵ					*/
	s16 acc_x_read, acc_y_read, acc_z_read;
	
	s32 gyr_x_mid = 0, gyr_y_mid = 0, gyr_z_mid = 0;		/*���ٶȶ���ֵ				*/
	s32 acc_x_mid = 0, acc_y_mid = 0, acc_z_mid = 0;
	
	s16 gyr_x_filter, gyr_y_filter, gyr_z_filter;
	s16 acc_x_filter, acc_y_filter, acc_z_filter;
	

	
	for (i = 0; i < 100; i++)
	{
//		MPU_Get_Gyroscope(&gyr_x_read, &gyr_y_read, &gyr_z_read);				/*���ؽǶ�ֵ����������	*/	
//																									
//		MPU_Get_Accelerometer(&acc_x_read, &acc_y_read, &acc_z_read);		/*���ؽ��ٶ�ֵ����������*/
		
		gyr_x_mid += gyr_x_read;																				/*�����ۼӣ��˲�				*/
		gyr_y_mid += gyr_y_read;
		gyr_z_mid += gyr_z_read;
		acc_x_mid += acc_x_read;
		acc_y_mid += acc_y_read;
		acc_z_mid += acc_z_read;
	}
	
	gyr_x_filter = gyr_x_mid / 100;												/*��ֵ�˲�							*/
	gyr_y_filter = gyr_y_mid / 100;
	gyr_z_filter= gyr_z_mid / 100;
	
	acc_x_filter = acc_x_mid / 100;
	acc_y_filter = acc_y_mid / 100;
	acc_z_filter = acc_z_mid / 100;
	
	qb_sz_status->init_gyr.X = gyr_x_filter;
	qb_sz_status->init_gyr.Y = gyr_y_filter;
	qb_sz_status->init_gyr.Z = gyr_z_filter;
	
	qb_sz_status->init_acc.X = acc_x_filter;
	qb_sz_status->init_acc.Y = acc_y_filter;
	qb_sz_status->init_acc.Z = acc_z_filter;
}
