#include "stm32f10x.h"                  // Device header



void encoder_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	//选择内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  //初始化时基单元
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1 ;//ARR周期
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;//PSC预分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);                            



TIM_ICInitTypeDef TIM_ICInitStructure;//初始化输入捕获单元
TIM_ICStructInit(&TIM_ICInitStructure);
TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 ;
TIM_ICInitStructure.TIM_ICFilter = 0xF;   // 
TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_ICStructInit(&TIM_ICInitStructure);
TIM_ICInitStructure.TIM_Channel = TIM_Channel_2 ;
TIM_ICInitStructure.TIM_ICFilter = 0xF;   //
TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

TIM_Cmd(TIM3,ENABLE);
}
int16_t encoder_Get(void)
{ 
	int16_t temp;
	temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return temp;
}
