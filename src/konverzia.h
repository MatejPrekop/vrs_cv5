/*
 * konverzia.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Mallto
 */

#ifndef KONVERZIA_H_
#define KONVERZIA_H_



#endif /* KONVERZIA_H_ */

int konverzia(void) {
		int AD_value;
		ADC_SoftwareStartConv(ADC1);
		while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {
		}
		AD_value = ADC_GetConversionValue(ADC1);
		return AD_value;
	}
