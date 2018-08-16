#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H
#include "stm32f10x.h"

typedef struct 
{
int zuo_shang_value;
int zuo_xia_value;
int you_shang_value;
int you_xia_value;
}Robot_attitude_mother;
typedef struct 
{
char  zuo_shang_flag;
char  zuo_xia_flag;
char  you_shang_flag;
char  you_xia_flag;
}Robot_flag_mother;
void Hal_Init_Pwm(void);
void uart3_config(void);
void SendWare1(void *areaddr, uint32_t waresize);
void TIM4_Mode_Config(void);
#endif

