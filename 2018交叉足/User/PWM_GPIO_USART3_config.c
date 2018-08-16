#include "stm32f10x.h"
#include "PWM_GPIO_USART3_config.h"

void uart3_config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART3, ENABLE);	
}
void Hal_Init_Pwm(void)
{  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE); 
  
  GPIO_InitTypeDef        GPIO_InitStructure_GPIOA;                  
  GPIO_InitStructure_GPIOA.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure_GPIOA.GPIO_Mode = GPIO_Mode_AF_PP;              
  GPIO_InitStructure_GPIOA.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure_GPIOA);  
	
	GPIO_InitTypeDef        GPIO_InitStructure_GPIOB;                  
  GPIO_InitStructure_GPIOB.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure_GPIOB.GPIO_Mode = GPIO_Mode_IN_FLOATING;              
  GPIO_InitStructure_GPIOB.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure_GPIOB);
	
	GPIO_InitTypeDef        GPIO_InitStructure_GPIOA_IN;                  
  GPIO_InitStructure_GPIOA_IN.GPIO_Pin =  GPIO_Pin_15;
  GPIO_InitStructure_GPIOA_IN.GPIO_Mode = GPIO_Mode_IN_FLOATING;              
  GPIO_InitStructure_GPIOA_IN.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure_GPIOA_IN);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure_TIM2;                 
  TIM_DeInit(TIM2);                                               
  TIM_TimeBaseStructure_TIM2.TIM_Period = 3999;                     
  TIM_TimeBaseStructure_TIM2.TIM_Prescaler = 359;              
  TIM_TimeBaseStructure_TIM2.TIM_ClockDivision = TIM_CKD_DIV1 ;      
  TIM_TimeBaseStructure_TIM2.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseStructure_TIM2.TIM_RepetitionCounter = 0;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure_TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure_TIM3;                 
  TIM_DeInit(TIM3);                                               
  TIM_TimeBaseStructure_TIM3.TIM_Period = 3999;                     
  TIM_TimeBaseStructure_TIM3.TIM_Prescaler = 359;              
  TIM_TimeBaseStructure_TIM3.TIM_ClockDivision = TIM_CKD_DIV1 ;      
  TIM_TimeBaseStructure_TIM3.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseStructure_TIM3.TIM_RepetitionCounter = 0;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure_TIM3);


  TIM_OCInitTypeDef       TIM_OCInitStructure_TIM2; 
  TIM_OCInitStructure_TIM2.TIM_OCMode = TIM_OCMode_PWM2;               
  TIM_OCInitStructure_TIM2.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure_TIM2.TIM_OCPolarity = TIM_OCPolarity_High;        
  
  TIM_OCInitStructure_TIM2.TIM_Pulse =0;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure_TIM2);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OCInitStructure_TIM2.TIM_Pulse =0;         
  TIM_OC2Init(TIM2, &TIM_OCInitStructure_TIM2);        
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OCInitStructure_TIM2.TIM_Pulse =0;       
  TIM_OC3Init(TIM2, &TIM_OCInitStructure_TIM2);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OCInitStructure_TIM2.TIM_Pulse =0;
  TIM_OC4Init(TIM2, &TIM_OCInitStructure_TIM2);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	
	TIM_OCInitTypeDef       TIM_OCInitStructure_TIM3; 
  TIM_OCInitStructure_TIM3.TIM_OCMode = TIM_OCMode_PWM2;               
  TIM_OCInitStructure_TIM3.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure_TIM3.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OCInitStructure_TIM3.TIM_Pulse =0;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure_TIM3);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure_TIM3.TIM_Pulse =0;         
  TIM_OC2Init(TIM3, &TIM_OCInitStructure_TIM3);        
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);   
	TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM2, ENABLE); 
  TIM_Cmd(TIM3, ENABLE); 	
}
void TIM4_Mode_Config(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
    TIM_TimeBaseStructure.TIM_Period=19999;
    TIM_TimeBaseStructure.TIM_Prescaler= 71;	
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}
/*********山外上位机波形显示*************/
void USART3_SendChar1(unsigned char b)
{
    while (USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
		USART_SendData(USART3,b);
}
void Uart_PutBuff1( uint8_t *buff, uint32_t len)
{
    while(len--)
    {
        USART3_SendChar1(*buff);
        buff++;
    }
}
void SendWare1(void *areaddr, uint32_t waresize)
{
    uint8_t cmdf[2] = {3, ~3};   
    uint8_t cmdr[2] = {~3, 3};    
		
    Uart_PutBuff1(cmdf, sizeof(cmdf));   
    Uart_PutBuff1((uint8_t *)areaddr, waresize);  
    Uart_PutBuff1(cmdr, sizeof(cmdr));   
}

