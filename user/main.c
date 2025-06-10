#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.H"
#include "body_hw.h"
#include "Buzzer.h"

uint16_t HwValue,Pre_HwValue;
uint16_t AD1;

int main(void)
{	
	OLED_Init();
	AD_Init();
	Body_Hw_Init();
	Buzzer_Init();
	Timer_Init();

	OLED_ShowString(0,0,"是否有人:",OLED_8X16);
	OLED_Update();
	OLED_ShowString(0,42,"AD1:",OLED_8X16);
	
	while(1)
	{	
		AD1=AD_GetValue(ADC_Channel_1);
		OLED_ShowNum(44,42,AD1,4,OLED_8X16);
		OLED_Update();
		HwValue = Body_Hw_GetData();
		
		if(HwValue!=Pre_HwValue)
		{
			if(HwValue == 1)
			{
				OLED_ShowString(0,22,"是",OLED_8X16);
				OLED_Update();
			}
			else
			{
				OLED_ShowString(0,22,"否",OLED_8X16);
				OLED_Update();
			}
		}
		
		if(HwValue == 1&AD1>200)
				{
					Buzzer_Flag = 1;
					Counter = 0;
				}
			
		Pre_HwValue = HwValue;
		
		Delay_ms(200);
	}
}
