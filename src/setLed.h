/*
 * setLed.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Mallto
 */

#ifndef SETLED_H_
#define SETLED_H_



#endif /* SETLED_H_ */

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
