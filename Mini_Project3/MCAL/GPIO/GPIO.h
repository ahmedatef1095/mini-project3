
#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_


#include "../../LIB/stdtypes.h"

//Configuration Ports =================================================================================

typedef enum {INPUT=0,OUTPUT}DIRECTION;

typedef enum {LOW=0,HIGH}STATE;

typedef enum {PA=0,PB,PC,PD}PORT_ID;

typedef enum {  A0=0,A1,A2,A3,A4,A5,A6,A7,
				B0=8,B1,B2,B3,B4,B5,B6,B7,
				C0=16,C1,C2,C3,C4,C5,C6,C7,
				D0=24,D1,D2,D3,D4,D5,D6,D7,
				TOTAL_PINS
				}PIN_ID;


void GPIO_InitPin(PIN_ID Pin , DIRECTION dir);
void GPIO_WritePin(PIN_ID Pin , STATE state);
STATE GPIO_ReadPin(PIN_ID Pin);

void GPIO_InitPort  (PORT_ID port , uint8 dir);
void GPIO_WritePort (PORT_ID port , uint8 value);
uint8 GPIO_ReadPort (PORT_ID port);

void GPIO_Pullup_Enable(PIN_ID Pin);
void GPIO_Pullup_Disable();


#endif
