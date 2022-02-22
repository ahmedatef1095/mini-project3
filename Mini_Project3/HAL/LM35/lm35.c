
#include <util/delay.h> /* For the delay functions */
#include "lm35.h"

#include "../../MCAL/ADC/adc.h"

void LM35_init()
{
	ADC_ConfigType Lm35_channel={ADC_VREF_256mV,ADC_PRESCALLER_8};
	ADC_init(&Lm35_channel);

}


uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	uint16 readChannel=ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Make delay for some time until g_adcResult value is updated with the ADC interrupt */
	_delay_ms(5);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)readChannel*SENSOR_MAX_TEMPERATURE*ADC_VREF_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

