/*
 * vrs_cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: Mallto
 */

#include "stm32l1xx.h"

extern uint16_t merana_hodnota=0;

void adc_init(void)
 {

 	ADC_InitTypeDef ADC_InitStructure;


 	/* Enable the HSI oscillator */
 	RCC_HSICmd(ENABLE);

 	/* Check that HSI oscillator is ready */
 	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
 	/* Enable ADC clock */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

 	/* Initialize ADC structure */
 	ADC_StructInit(&ADC_InitStructure);

 	/* ADC1 configuration */
 	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
 	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
 	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
 	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
 	ADC_InitStructure.ADC_NbrOfConversion = 1;
 	ADC_Init(ADC1, &ADC_InitStructure);

 	/* ADCx regular channel8 configuration */
 	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_16Cycles);
 	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
 	ADC_ITConfig(ADC1,ADC_IT_OVR,ENABLE);

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
 	NVIC_InitTypeDef NVIC_InitStructure;
 	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn; //zoznam prerušení nájdete v
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);

 	/* Enable the ADC */
 	ADC_Cmd(ADC1, ENABLE);

 	/* Wait until the ADC1 is ready */
 	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);
 	ADC_SoftwareStartConv(ADC1);
 	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) asm ("nop");

 }

 void gpio_init(void)
 {
 	GPIO_InitTypeDef GPIO_InitStructure;

 	/* Enable GPIO clock */
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

 	/*Configure GPIO pin : PA5 */
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	/* Configure ADCx Channel 0 as analog input */
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 }

void setLed(void) {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpioInitStruc;

	gpioInitStruc.GPIO_Pin = GPIO_Pin_5;
	gpioInitStruc.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruc.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc.GPIO_PuPd = GPIO_PuPd_UP;
	gpioInitStruc.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &gpioInitStruc);
}

int konverzia(void) {
	int AD_value;
	ADC_SoftwareStartConv(ADC1);
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {
	}
	AD_value = ADC_GetConversionValue(ADC1);
	return AD_value;
}

/*void nvic_fun(void){
 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn; //zoznam prerušení v stm32l1xx.h
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);

 }
 */

void ADC1_IRQHandler(void) {
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {
		merana_hodnota = ADC1->DR;
	}
	if (ADC_GetFlagStatus(ADC1,ADC_SR_OVR))	ADC_ClearFlag(ADC1,ADC_FLAG_OVR);
}
