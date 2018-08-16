#include "stm32f10x.h" 
#include "PWM_GPIO_USART3_config.h"
float var1[3]={0.0};//������Ҫ���͵�����
#define Hongwai_zuo  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
#define Hongwai_you  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)

#define Huidu_zuo  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define Huidu_you  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)

#define Key_zuo  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define Key_you  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)

#define FULL_DUTY   4000
Robot_attitude_mother Robot_attitude;
Robot_flag_mother     Robot_flag;
extern Robot_attitude_mother Robot_attitude;
extern Robot_flag_mother     Robot_flag;
int Number_flag_zuo=0;
int Number_flag_you=0;
int attitude_flag_zuo=0;
int attitude_flag_you=0;
int critick=0;
int test[6]={0};
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
void Robot_init(void);
void PWM_current(void);
void qianjin(uint16_t number,int jiaodu );
int  main(void)
{
	Hal_Init_Pwm();
	uart3_config();
	Robot_init();
	TIM4_Mode_Config();
	while(1)
	{
		SendWare1((float *)var1, sizeof(var1));
	}
}
/**
  ******************************************************************************
  * @file    main.c
  * @author  Lingsu Team
  * @version V3.5.0
  * @date    11-August-2018
  * @brief  ���趨ʱ��Ϊ20ms���ڡ�
  ******************************************************************************/
void TIM4_IRQHandler(void)
{
		if ( TIM_GetITStatus( TIM4, TIM_IT_Update) != RESET ) 
	{	
		
		   critick++;
		  if(critick>=300)
			{
				PWM_current();
				qianjin(5,0);
			}
			
		
		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);  		 
	}		
}
void Robot_init(void)
{
	Robot_attitude.you_shang_value=150;
	Robot_attitude.you_xia_value =300;
	Robot_attitude.zuo_shang_value =450;
	Robot_attitude.zuo_xia_value=300;
}
void PWM_current(void)
{
			  TIM2->CCR1=FULL_DUTY-Robot_attitude.you_xia_value;
				TIM2->CCR2=0;
				TIM2->CCR3=FULL_DUTY-Robot_attitude.you_shang_value;
				TIM2->CCR4=FULL_DUTY-Robot_attitude.zuo_shang_value;
		    TIM3->CCR1=0;
		    TIM3->CCR2=FULL_DUTY-Robot_attitude.zuo_xia_value;
}
/**
  ******************************************************************************
  * @file    main.c
  * @author  Lingsu Team
  * @version V3.5.0
  * @date    11-August-2018
  * @brief   jiaodu��+��ʾ�ҹգ�-��ʾ��գ�����ֵ��С��ʾ�սǴ�С��0�ȴ���ֱ��
             number: ����ǰ������.
  ******************************************************************************/
void qianjin(uint16_t number,int jiaodu )
{
	if(Number_flag_zuo<=number&&Number_flag_you<=number)
	 {
				//�����
				if(Robot_flag.zuo_shang_flag==1&&Robot_flag.you_shang_flag ==0&&attitude_flag_zuo==0&&attitude_flag_you==0)
				{
						if(Robot_flag.zuo_xia_flag ==0)
						{
								Robot_attitude.zuo_xia_value+=150;
						}
						if(Robot_flag.you_xia_flag ==0)
						{
								Robot_attitude.you_xia_value-=150; 
						}
						if(Robot_attitude.zuo_xia_value>=3300)
						{
								Robot_flag.zuo_xia_flag =0;
							  attitude_flag_zuo=1;
						}
						if(Robot_attitude.you_xia_value<=2700)
						{
								Robot_flag.you_xia_flag =1;
							  attitude_flag_you=1;
						}
				}
				//��ǰ��
				if(Robot_flag.zuo_xia_flag==0&&Robot_flag.you_xia_flag ==1&&attitude_flag_zuo==1&&attitude_flag_you==1)
				{
						if(Robot_flag.zuo_shang_flag  ==1)
						{
								Robot_attitude.zuo_shang_value-=150;
						}
						if(Robot_flag.you_shang_flag ==0)
						{
								Robot_attitude.you_shang_value+=150; 
						}
						if(Robot_attitude.zuo_shang_value<=1500)
						{
								Robot_flag.zuo_shang_flag =0;
							  attitude_flag_zuo=2;
						}
						if(Robot_attitude.you_shang_value>=4500)
						{
								Robot_flag.you_shang_flag =1;
							  attitude_flag_you=2;
						}
				}	
				//�����
				if(Robot_flag.zuo_shang_flag==0&&Robot_flag.you_shang_flag ==1&&attitude_flag_zuo==2&&attitude_flag_you==2)
				{
						if(Robot_flag.zuo_xia_flag  ==0)
						{
								Robot_attitude.zuo_xia_value-=150;
						}
						if(Robot_flag.you_xia_flag ==1)
						{
								Robot_attitude.you_xia_value+=150; 
						}
						if(Robot_attitude.zuo_xia_value<=3000)
						{
								Robot_flag.zuo_xia_flag =0;
							  attitude_flag_zuo=3;
						}
						if(Robot_attitude.you_xia_value>=3000)
						{
								Robot_flag.you_xia_flag =0;
							  attitude_flag_you=3;
						}
				}
				//�����
				if(Robot_flag.zuo_shang_flag==0&&Robot_flag.you_shang_flag ==1&&attitude_flag_zuo==3&&attitude_flag_you==3)
				{
						if(Robot_flag.zuo_xia_flag ==0)
						{
								Robot_attitude.zuo_xia_value-=150;
						}
						if(Robot_flag.you_xia_flag ==0)
						{
								Robot_attitude.you_xia_value+=150; 
						}
						if(Robot_attitude.zuo_xia_value<=2700)
						{
								Robot_flag.zuo_xia_flag =1;
							  attitude_flag_zuo=4;
						}
						if(Robot_attitude.you_xia_value>=3300)
						{
								Robot_flag.you_xia_flag =0;
							  attitude_flag_you=4;
						}
				}
				//��ǰ��
				if(Robot_flag.zuo_xia_flag==1&&Robot_flag.you_xia_flag ==0&&attitude_flag_zuo==4&&attitude_flag_you==4)
				{
						if(Robot_flag.zuo_shang_flag  ==0)
						{
								Robot_attitude.zuo_shang_value+=150;
						}
						if(Robot_flag.you_shang_flag ==1)
						{
								Robot_attitude.you_shang_value-=150; 
						}
						if(Robot_attitude.zuo_shang_value>=4500)
						{
								Robot_flag.zuo_shang_flag =1;
							  attitude_flag_zuo=5;
						}
						if(Robot_attitude.you_shang_value<=1500)
						{
								Robot_flag.you_shang_flag =0;
							  attitude_flag_you=5;
						}
				}	
				//�����
				if(Robot_flag.zuo_shang_flag==1&&Robot_flag.you_shang_flag ==0&&attitude_flag_zuo==5&&attitude_flag_you==5)
				{
						if(Robot_flag.zuo_xia_flag  ==1)
						{
								Robot_attitude.zuo_xia_value+=150;
						}
						if(Robot_flag.you_xia_flag  ==0)
						{
								Robot_attitude.you_xia_value-=150; 
						}
						if(Robot_attitude.zuo_xia_value>=3000)
						{
								Robot_flag.zuo_xia_flag =0;
							  attitude_flag_zuo=0;
								Number_flag_zuo++;
						}
						if(Robot_attitude.you_xia_value<=3000)
						{
								Robot_flag.you_xia_flag =0;
							  attitude_flag_you=0;
								Number_flag_zuo++;
						}
				}
   }
}






