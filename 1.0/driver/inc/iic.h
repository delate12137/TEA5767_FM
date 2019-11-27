#ifndef _stm32_iic_
#define _stm32_iic_

#include "stm32f10x.h"
#include "delay.h"

#define IIC_PORT GPIOB
#define IIC_SDA GPIO_Pin_11
#define IIC_SCL GPIO_Pin_10
#define ICC_CLOCK RCC_APB2Periph_GPIOB


void SDA_IN(void);
void SDA_OUT(void);
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t ack);
uint8_t IIC_Wait_Ack(void); 	
void IIC_Ack(void);
void IIC_NAck(void);


#endif