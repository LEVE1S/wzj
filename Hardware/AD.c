#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);		//开启RCC ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//开启GPIOA时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//ADC分频，72/6=12  大于14不可用
	
	GPIO_InitTypeDef GPIO_InitStructure;	//配置GPIO A0口为ADC模式
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AIN;	//AIN模拟输入下，GPIO无效
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	ADC_InitTypeDef ADC_InitStructure;		//结构体初始化ADC
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//不使用连续转换，使用单次转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//触发控制的触发源 不使用外部触发，使用软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式 独立模式 ADC1和ADC2各转换各的
	ADC_InitStructure.ADC_NbrOfChannel = 1;		//通道数目1
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//扫描转换模式 非扫描
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);	//开启ADC电源
	
	ADC_ResetCalibration(ADC1);		//复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);		//等到复位校准完成
	ADC_StartCalibration(ADC1);		//开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);		//等到校准完成
}

uint16_t AD_GetValue(uint8_t ADC_Channel)		//启动转换获取结果
{	
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);	//选择规则组输入通道 ADC1、通道0、序列1、采样时间55.5个ADCCLK周期（更快的转换参数小，更稳定参数大）
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);		//软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);		//获取标志位状态 规则组转换完成标志位
	return ADC_GetConversionValue(ADC1);	//获取结果
}
