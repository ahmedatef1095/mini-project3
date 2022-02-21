
#ifndef ADC_H_
#define ADC_H_

#include "../../LIB/std_types.h"

#define ADC_MAXIMUM_VALUE    (1023)
#define ADC_VREF_VALUE       (2.56)

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;


/*ADC Vref Source*/
typedef enum
{
	VREF_AREF=0,
	VREF_AVCC,
	VREF_256mV,
}ADC_ReferenceVolatge;


/*ADC PreScaler*/
typedef enum
{
	ADC_PRESCALLER_2=1,
	ADC_PRESCALLER_4,
	ADC_PRESCALLER_8,
	ADC_PRESCALLER_16,
	ADC_PRESCALLER_32,
	ADC_PRESCALLER_64,
	ADC_PRESCALLER_128,
}ADC_Prescaler;


typedef struct
{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;


void ADC_init(const ADC_ConfigType * Config_Ptr);
uint16 ADC_readChannel(uint8 channel);


#endif /* MCAL_ADC_ADC_H_ */
