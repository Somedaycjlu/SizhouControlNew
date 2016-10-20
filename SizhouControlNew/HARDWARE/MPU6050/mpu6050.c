#include "mpu6050.h"

//MPU6050初始化
u8 MPU_Init(void)
{
	u8 read_address;
	MPU_IIC_Init();
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);					//0X80:1000 0000
	delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);					//唤醒MPU6050
	MPU_Set_Gyro_Fsr(3);					//陀螺仪量程+-2000dps	猜想：在四轴调的稳了之后可以把陀螺仪量程缩小
	MPU_Set_Accel_Fsr(0);					//加速度计量程+-2g
	MPU_Set_Rate(500);						//设置采样率：500HZ
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//IIC主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);			//关闭FIF0
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	read_address=MPU_Read_Byte(MPU_DEVICE_ID_REG); 
	MPU_Write_Byte(MPU_CFG_REG,0X04);					//20HZ
	MPU_Write_Byte(MPU_SAMPLE_RATE_REG,0X04);
	
	if(read_address==MPU_ADDR)											//器件ID正确
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL PLL X轴作为参考轴
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度计陀螺仪都工作
		MPU_Set_Rate(500);													//设置采样率：500HZ
 	}else return 1;
	return 0;
}

//设置MPU6050陀螺仪传感器满量程范围
//fsr：0 ，+-250dps；1，+-500dps；2，+-1000；3，+-2000dps
//返回值：设置成功（0）；设置失败（其他）
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);  
}

//设置MPU6050加速度传感器满量程范围
//fsr：0 ，+-2g；1，+-4g；2，+-8g；3，+-16g
//返回值：设置成功（0）；设置失败（其他）
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//ÉèÖÃ¼ÓËÙ¶È´«¸ÐÆ÷ÂúÁ¿³Ì·¶Î§  
}

//设置MPU6050的采样率 rate（4~1000HZ）
//返回值：设置成功（0）；设置失败（其他）
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);				//设置数字低通滤波器
// 	return MPU_Set_LPF(rate/2);														//自动设置LPF为采样率的一半
		return MPU_Set_LPF(rate/25);														//自动设置LPF为采样率的一半
}

//设置MPU6050D的数字低通滤波器
//lpf：数字低通滤波器频率
//返回值：设置成功（0）；设置失败（其他）
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//ÉèÖÃÊý×ÖµÍÍ¨ÂË²¨Æ÷  
}

//IIC连续写 addr：器件地址 ；reg：寄存器地址 ；len：写入长度；buf：数据区；
//返回值：正常（0）；不正常（其他）
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);			//发送器件地址+写命令
	if(MPU_IIC_Wait_Ack())							//等待应答
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);							//写寄存器地址
    MPU_IIC_Wait_Ack();								//等待应答
	for(i=0;i<len;i++)
	{
		MPU_IIC_Send_Byte(buf[i]);					//发送数据
		if(MPU_IIC_Wait_Ack())						//等待ACK
		{
			MPU_IIC_Stop();	 
			return 1;		 
		}		
	}    
    MPU_IIC_Stop();	 
	return 0;	
} 

//IIC连续读 addr：器件地址 ；reg：寄存器地址 ；len：写入长度；buf：数据区；
//返回值：正常（0）；不正常（其他）
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);						//发送器件地址+写命令
	if(MPU_IIC_Wait_Ack())										//等待应答
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);										//写寄存器地址
    MPU_IIC_Wait_Ack();											//等待应答
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((addr<<1)|1);						//发送器件地址+读命令	
    MPU_IIC_Wait_Ack();											//等待应答
	while(len)
	{
		if(len==1)*buf=MPU_IIC_Read_Byte(0);			//读数据，发送NACK
		else *buf=MPU_IIC_Read_Byte(1);					//读数据，发送ACK
		len--;
		buf++; 
	}    
    MPU_IIC_Stop();													//产生一个停止条件
	return 0;	
}

//IIC写一个字节 reg：寄存器地址；data：数据
//返回值：正常（0）；不正常（其他）
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);			//发送器件地址+读命令	
	if(MPU_IIC_Wait_Ack())										//等待应答
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);										//写寄存器地址
    MPU_IIC_Wait_Ack();											//等待应答
	MPU_IIC_Send_Byte(data);									//发送数据
	if(MPU_IIC_Wait_Ack())										//等待ACK
	{
		MPU_IIC_Stop();	 
		return 1;		 
	}		 
    MPU_IIC_Stop();	 
	return 0;
}

//IIC读一个字节 reg：寄存器地址；data：数据
//返回值：正常（0）；不正常（其他）
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);				//发送器件地址+写命令	
	MPU_IIC_Wait_Ack();												//等待应答
    MPU_IIC_Send_Byte(reg);											//写寄存器地址
    MPU_IIC_Wait_Ack();												//等待应答
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|1);				//发送器件地址+读命令	
    MPU_IIC_Wait_Ack();												//等待应答
	res=MPU_IIC_Read_Byte(0);										//读取数据，发送NACK
    MPU_IIC_Stop();														//产生一个停止条件
	return res;		
}

//得到陀螺仪原始值（带符号） gx：陀螺仪X轴；gy：陀螺仪Y轴; gz：陀螺仪Z轴
//返回值：成功（0）；不成功（其他）
u8 MPU_Get_Accelerometer(int16_t *gx,int16_t*gy,int16_t*gz)	
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gy=((u16)buf[0]<<8)|buf[1];
		*gx=((u16)buf[2]<<8)|buf[3]; 
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

//得到加速度计原始值（带符号） ax：加速度计X轴；ay：加速度计Y轴; az：加速度计Z轴
//返回值：成功（0）；不成功（其他）
u8 MPU_Get_Gyroscope(int16_t*ax,int16_t *ay,int16_t*az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];
		*ay=((u16)buf[2]<<8)|buf[3];
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}


