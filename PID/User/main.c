#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "encoder.h"
#include "motor.h"

int16_t Speed;


int main(void)
{   
	OLED_Init();
	Timer_Init();	encoder_Init();
	motor_Init();
	OLED_ShowString(1,1,"CNT:");
    OLED_ShowString(1,1,"CNT:");
	while(1)
	{
		OLED_ShowSignedNum(1,5,Speed,5);
	}
	
	
}
void TIM2_IRQHandler(void)
    {	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	  {
		Speed = encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
	  }

	
    }


