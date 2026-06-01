#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//打开AFIO时钟
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//重映射引脚（定时器通道从PA0到PA15)
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//解除调试端口
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM2);//选择内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  //初始化时基单元
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1 ;//ARR周期
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;//PSC预分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较单元
	TIM_OCStructInit(&TIM_OCInitStructure);//把这个结构体全体赋初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1 ;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High ;//设置输出比较极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;//设置输出使能
	TIM_OCInitStructure.TIM_Pulse = 50;//设置CCR
	TIM_OC3Init(TIM2,&TIM_OCInitStructure); 
	
	TIM_Cmd(TIM2,ENABLE);
}	
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2,Compare);
}