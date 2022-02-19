

#ifndef ADC_H_
#define ADC_H_


#include "../../LIB/stdtypes.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_VREF_VALUE       5

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;


/*ADC Vref Source*/
#define ADC_VREF          VREF_AVCC
#define VREF_AREF         0
#define VREF_AVCC         1
#define VREF_256mV        2

/*ADC Adjusted*/
#define ADC_Adjusted              ADC_Right_Adjusted
//->please select Adjust
#define ADC_Left_Adjusted                       1       // 10bits = ADCH (2bits)+ ADCL (8bits)  need to shift     0b0000 0000 00xx xxxx
#define ADC_Right_Adjusted                      0		// 10bits = ADCH (8bits)+ ADCL (2bits)  no need to shift  0bxxxx xx00 0000 0000

#define ADC_MODE                   AUTO_TRIGGER       //select  1
//->please select  ADC Mode
#define AUTO_TRIGGER                    1        // Modes from data sheet
#define SINGLE_CONVERSION               0		 // Modes from data sheet

/**/
#define ADC_PRESCALLER        	      ADC_PreScaler_128
//->please select PreScaler
#define ADC_PreScaler_2              	0b00000000      // PreScaler by /2
#define ADC_PreScaler_4			     	0b00000010		 // PreScaler by /4
#define ADC_PreScaler_8             	0b00000011		 // PreScaler by /8
#define ADC_PreScaler_16				0b00000100      // PreScaler by /16
#define ADC_PreScaler_32           	 	0b00000101      // PreScaler by /32
#define ADC_PreScaler_64		   		0b00000110		 // PreScaler by /64
#define ADC_PreScaler_128               0b00000111		 // PreScaler by /128
#define ADC_PreScaler_Crl_Mask          0b11111000      // To clear LS 3 bits ( Crl_Mask & Any Mask )

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

/*
typedef enum
{
	ADC_FINISH=1,
	ADC_NOT_FINISH=0
}ADC_Status;
*/

/*
#define ADC_Vref                   ADC_Vref_2_56v      //select  1
//->please select  1 Vref
#define ADC_Vref_AVCC              0b0100 0000      // Modes from data sheet
#define ADC_Vref_AREF              0b0000 0000		// Modes from data sheet
#define ADC_Vref_2.56v             0b1100 0000		// Modes from data sheet
#define ADC_Vref_Crl_Mask          0b0011 1111      // To clear MS 2 bits
#define ADC_Vref_mv                5000
#define ADC_Max_NOS                1024           //MAX Number of Steps
*/


void ADC_init();
uint16 ADC_readChannel(uint8 channel);

/*
ADC_Status ADC_TriggerByPeripheral(ADC_Trigger source);
ADC_Status ADC_GETRead_UsingInterrupt(ADC_Channel channel,uint16 *dig_val);
*/
void ADC_INT_Enable(void);
void ADC_INT_Disable(void);



#endif /* MCAL_ADC_ADC_H_ */
