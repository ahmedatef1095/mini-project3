
#ifndef ADC_H_
#define ADC_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE        (1023)
#define ADC_REF_VOLT_VALUE       (2.56)

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*ADC Vref Source*/
typedef enum
{
	ADC_VREF_AREF=0,
	ADC_VREF_AVCC=1,
	ADC_VREF_256mV=3,
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

/*ADC configuration structure*/
typedef struct
{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup ADC configuration.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Read the required Channel of ADC.
 * return the value of ADC register
 */
uint16 ADC_readChannel(uint8 channel);


#endif /* ADC_H_ */
