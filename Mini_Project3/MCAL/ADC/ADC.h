
#ifndef ADC_H_
#define ADC_H_

#include "../../LIB/stdtypes.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_VREF_VALUE       5

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;


/*ADC Vref Source*/
typedef enum
{
 VREF_AREF=0,
 VREF_AVCC,
 VREF_256mV,
}ADC_ReferenceVolatge;



/*ADC Adjusted*/
#define ADC_Adjusted                   ADC_Right_Adjusted
//->please select Adjust
#define ADC_Left_Adjusted                   1       // 10bits = ADCH (2bits)+ ADCL (8bits)  need to shift     0b0000 0000 00xx xxxx
#define ADC_Right_Adjusted                  0		// 10bits = ADCH (8bits)+ ADCL (2bits)  no need to shift  0bxxxx xx00 0000 0000

/*ADC Mode*/
#define ADC_MODE                    AUTO_TRIGGER       //select  1
//->please select  ADC Mode
#define AUTO_TRIGGER                    1        // Modes from data sheet
#define SINGLE_CONVERSION               0		 // Modes from data sheet

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





/*ADC AUTO TRIGGER SOURCE*/
#define  ADC_AUTO_TRIGGER_SOURCE         FREE_RUNNING
//->if select Auto_Trigger Source Select
#define FREE_RUNNING              	     0b00000000
#define ANALOG_COMARATOR			     0b00100000
#define EXT_INT0					     0b01000000
#define TIMER0_COMPARE			  		 0b11000000
#define TIMER0_OVERFLOW        			 0b10000000
#define TIMER1_COMPARE			   		 0b10100000
#define TIMER1_OVERFLOW			   		 0b11000000
#define TIMER1_CAPTURE			   		 0b11100000
#define Source_Crl_Mask			   		 0b00011111





typedef struct
{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;



void ADC_init(const ADC_ConfigType * Config_Ptr);
uint16 ADC_readChannel(uint8 channel);


void ADC_INT_Enable(void);
void ADC_INT_Disable(void);



#endif /* MCAL_ADC_ADC_H_ */
