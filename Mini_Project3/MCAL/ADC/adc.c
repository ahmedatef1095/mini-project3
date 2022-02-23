
#include "adc.h"
#include <avr\io.h>

#include "../../lib/common_macros.h" /* To use the macros like SET_BIT */


void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/*ADC Vref Source*/
	ADMUX = (ADMUX & 0x3F) | ( (Config_Ptr->ref_volt<<6) & 0xC0);

	/*select PreScaler*/
	ADCSRA |=Config_Ptr->prescaler;

	/*ADC AUTO TRIGGER SOURCE*/
	/*ADC_Enable*/
	ADCSRA |=(1<<ADEN);

}


uint16 ADC_readChannel(uint8 channel)
{

	ADMUX = (ADMUX & 0XE0) | (channel & 0x07); /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(GET_BIT(ADCSRA,ADIF) == 0); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */

}
