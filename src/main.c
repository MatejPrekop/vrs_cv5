/*
 ******************************************************************************
 File:     main.c
 Info:     Generated by Atollic TrueSTUDIO(R) 6.0.0   2016-10-18

 The MIT License (MIT)
 Copyright (c) 2009-2016 Atollic AB

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 ******************************************************************************
 */
///
/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"
#include "vrs_cv5.h"

/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void) {
	int i = 0;

	/**
	 *  IMPORTANT NOTE!
	 *  See the <system_*.c> file and how/if the SystemInit() function updates
	 *  SCB->VTOR register. Sometimes the symbol VECT_TAB_SRAM needs to be defined
	 *  when building the project if code has been located to RAM and interrupts
	 *  are used. Otherwise the interrupt table located in flash will be used.
	 *  E.g.  SCB->VTOR = 0x20000000;
	 */

	/**
	 *  At this stage the microcontroller clock setting is already configured,
	 *  this is done through SystemInit() function which is called from startup
	 *  file (startup_stm32l1xx_hd.s) before to branch to application main.
	 *  To reconfigure the default setting of SystemInit() function, refer to
	 *  system_stm32l1xx.c file
	 */

	/* TODO - Add your application code here */



	adc_init();
	setLed();

	int merana_hodnota;
	int x;
	/* Infinite loop */
	while (1) {
		merana_hodnota = konverzia();

		if (merana_hodnota < 1300) {
			for (x = 0; x < 100000; x++) {
			}
			GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		}
		if ((merana_hodnota >= 1300) & (merana_hodnota < 2600)) {
			for (x = 0; x < 500000; x++) {
			}
			GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		}
		if (merana_hodnota >= 2600) {
			for (x = 0; x < 1000000; x++) {
			}
			GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		}

	}
	return 0;
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func,
		const char *failedexpr) {
	while (1) {
	}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr) {
	__assert_func(file, line, NULL, failedexpr);
}
