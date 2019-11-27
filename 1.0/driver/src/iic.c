#include "iic.h"

void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=IIC_SDA;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_PORT,&GPIO_InitStruct);
}
void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=IIC_SDA;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_PORT,&GPIO_InitStruct);
}

void IIC_Init(void)
{
	RCC_APB2PeriphClockCmd(ICC_CLOCK,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=IIC_SDA|IIC_SCL;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_PORT,&GPIO_InitStruct);
	GPIO_SetBits(IIC_PORT,IIC_SCL|IIC_SDA);
}
void IIC_Start(void)
{
	SDA_OUT();
	GPIO_SetBits(IIC_PORT,IIC_SCL|IIC_SDA);
	delay_us(5);
	GPIO_ResetBits(IIC_PORT,IIC_SDA);
	delay_us(5);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
}
void IIC_Stop(void)
{
	SDA_OUT();
	GPIO_ResetBits(IIC_PORT,IIC_SDA|IIC_SCL);
	delay_us(5);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delay_us(5);
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	delay_us(5);
}
void IIC_Send_Byte(uint8_t txd)
{
	SDA_OUT();
	uint8_t i;
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	for(i=0;i<8;i++)
	{
		if((txd&0x80)>>7)
			GPIO_SetBits(IIC_PORT,IIC_SDA);
		else
			GPIO_ResetBits(IIC_PORT,IIC_SDA);
		txd<<=1;
		delay_us(2);
		GPIO_SetBits(IIC_PORT,IIC_SCL);
		delay_us(2);
		GPIO_ResetBits(IIC_PORT,IIC_SCL);
		delay_us(2);
	}
}
uint8_t IIC_Read_Byte(uint8_t ack)
{
	SDA_IN();
	uint8_t temp;
	uint8_t i;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(IIC_PORT,IIC_SCL);
		delay_us(2);
		GPIO_SetBits(IIC_PORT,IIC_SCL);
		temp<<=1;
		if(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA))
		temp|=0x01;
		delay_us(1);
	}
	if (!ack)
		IIC_NAck();
	else
    	IIC_Ack();
	return temp;
}
void IIC_Ack(void)
{
	SDA_OUT();
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	delay_us(1);
	GPIO_ResetBits(IIC_PORT,IIC_SDA);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delay_us(5);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	GPIO_SetBits(IIC_PORT,IIC_SDA);
}
void IIC_NAck(void)
{
	SDA_OUT();
	GPIO_ResetBits(IIC_PORT,IIC_SCL|IIC_SDA);
	delay_us(1);
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delay_us(5);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	GPIO_SetBits(IIC_PORT,IIC_SDA);
}
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	delay_us(1);
	GPIO_SetBits(IIC_PORT,IIC_SCL);	 
	while(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 0;
		}
	}
	GPIO_SetBits(IIC_PORT,IIC_SCL);  
	return 1;  
} 

