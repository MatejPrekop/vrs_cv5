/*
 * vrs_cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: Mallto
 */

#include "stm32l1xx.h"
uint16_t merana_hodnota;
char posielana_hodnota[10];
int mod = 0;
int x = 0;

void adc_init(void) {

	/* Enable the HSI oscillator */
	RCC_HSICmd(ENABLE);

	/* Check that HSI oscillator is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
		;
	/* Enable ADC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* Initialize ADC structure */
	ADC_InitTypeDef ADC_InitStructure;
	ADC_StructInit(&ADC_InitStructure);

	/* ADC1 configuration */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 10;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADCx regular channel8 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);
	ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_255Cycles);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn; //zoznam prerušení nájdete v
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the ADC */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait until the ADC1 is ready */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
		;
	ADC_SoftwareStartConv(ADC1);

}

void gpio_init(void) {
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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC1_IRQHandler(void) {

	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {

		merana_hodnota = ADC_GetConversionValue(ADC1);
	}
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_OVR))
		ADC_ClearFlag(ADC1, ADC_FLAG_OVR);

}

void USART_init(void) {
	GPIO_InitTypeDef USART_GPIOStructure;
	USART_GPIOStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	USART_GPIOStructure.GPIO_Mode = GPIO_Mode_AF;
	USART_GPIOStructure.GPIO_Speed = GPIO_Speed_40MHz;
	USART_GPIOStructure.GPIO_OType = GPIO_OType_PP;
	USART_GPIOStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &USART_GPIOStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitStructure.USART_BaudRate = 9800;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	NVIC_InitTypeDef NVIC_USARTInitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_USARTInitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_USARTInitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_USARTInitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_USARTInitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_USARTInitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void) {
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)) {
		if (USART_ReceiveData(USART2) == 'm') {
			if (mod == 0) {
				mod = 1;
			} else {
				mod = 0;
			}
		}
		// kontrola flagu prerusenia

		if (USART_GetFlagStatus(USART2, USART_FLAG_TC)) {
			USART_ClearFlag(USART2, USART_FLAG_RXNE);
			USART_ClearFlag(USART2, USART_FLAG_TC);

		}

	}
}
void Send_String(char* string) {
	int i = 0;
	while (string[i] != 0) {
		// prenos charu z prebrateho stringu
		USART_SendData(USART2, string[i]);
		i++;
		// cakanie na dokoncenie prenosu
		while (!USART_GetFlagStatus(USART2, USART_FLAG_TC))
			;
	}
}
