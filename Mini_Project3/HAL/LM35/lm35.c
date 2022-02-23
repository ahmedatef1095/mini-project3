
#include "lm35.h"
#include <util/delay.h>
#include "../../mcal/adc/adc.h"
#include "../../mcal/gpio/gpio.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Setup LM35 Sensor and ADC configuration.
 */
void LM35_init()
{
	ADC_ConfigType Lm35_channel={ADC_VREF_256mV,ADC_PRESCALLER_8};
	ADC_init(&Lm35_channel);
	GPIO_setupPinDirection(PORTA_ID,PIN2_ID,PIN_INPUT);
	_delay_ms(300);
}

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void)
{
	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	adc_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return adc_value;
}



