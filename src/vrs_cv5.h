/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Mallto
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_

#endif /* VRS_CV5_H_ */
extern uint16_t merana_hodnota;
extern char posielana_hodnota[10];
extern int mod;
void adc_init(void);
void gpio_init(void);

int konverzia(void);
void nvic_fun(void);
void ADC1_IRQHandler(void);
void USART_init(void);
void USART1_IRQHandler(void);

