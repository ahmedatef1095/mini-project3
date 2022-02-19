
#include "GPIO.h"
#include <avr\io.h>
#include "../../LIB/macros.h"

void GPIO_InitPin (PIN_ID pin , DIRECTION dir)
{
	PORT_ID port=pin/8;
	pin%=8;
	switch (dir)
	{
		case(OUTPUT):
			switch(port)
			{
				case(PA):SET_BIT(DDRA,pin); break;
				case(PB):SET_BIT(DDRB,pin); break;
				case(PC):SET_BIT(DDRC,pin); break;
				case(PD):SET_BIT(DDRD,pin); break;
			}
		break;

		case(INPUT):
			switch(port)
			{
				case(PA):CLR_BIT(DDRA,pin); break;
				case(PB):CLR_BIT(DDRB,pin); break;
				case(PC):CLR_BIT(DDRC,pin); break;
				case(PD):CLR_BIT(DDRD,pin); break;

			}
		break;
	 }
}


void GPIO_WritePin(PIN_ID pin , STATE state)
{
	PORT_ID port=pin/8;
	pin%=8;
	switch(state)
	{
		case(HIGH):
			switch(port)
				{
					case(PA):SET_BIT(PORTA,pin); break;
					case(PB):SET_BIT(PORTB,pin); break;
					case(PC):SET_BIT(PORTC,pin); break;
					case(PD):SET_BIT(PORTD,pin); break;

				}
		break;

	case(LOW):
		switch(port)
			{
				case(PA):CLR_BIT(PORTA,pin); break;
				case(PB):CLR_BIT(PORTB,pin); break;
				case(PC):CLR_BIT(PORTC,pin); break;
				case(PD):CLR_BIT(PORTD,pin); break;
			}
	break;
		
	}
}


STATE GPIO_ReadPin(PIN_ID pin)
{		STATE state;
		PORT_ID port=pin/8;
		pin%=8;
		switch(port)
		{
			case(PA):state= GET_BIT(PINA,pin); break;
			case(PB):state= GET_BIT(PINB,pin); break;
			case(PC):state= GET_BIT(PINC,pin); break;
			case(PD):state= GET_BIT(PIND,pin); break;

		}
		return state;
}

void GPIO_InitPort  (PORT_ID port , uint8 dir)
{
	switch(dir)
	{
		default:
			switch(port)
			{
				case PA:DDRA=dir; break;
				case PB:DDRB=dir; break;
				case PC:DDRC=dir; break;
				case PD:DDRD=dir; break;
			}
		break;
		case(OUTPUT):
				switch(port)
				{
					case (PA):DDRA=0xff; break;
					case (PB):DDRB=0xff; break;
					case (PC):DDRC=0xff; break;
					case (PD):DDRD=0xff; break;
				}
		break;
		case(INPUT):
			switch(port)
			{
				case (PA):DDRA=0x00; break;
				case (PB):DDRB=0x00; break;
				case (PC):DDRC=0x00; break;
				case (PD):DDRD=0x00; break;
			}
		break;

	}
}
void GPIO_WritePort (PORT_ID port , uint8 value)
{
switch(port)
	{
		case PA:PORTA=value; break;
		case PB:PORTB=value; break;
		case PC:PORTC=value; break;
		case PD:PORTD=value; break;
	}
}
uint8 GPIO_ReadPort(PORT_ID port )
{	uint8 value;
	switch(port)
		{
			case PA: value= PINA; break;
			case PB: value= PINB; break;
			case PC: value= PINC; break;
			case PD: value= PIND; break;
		}
	return value;

}

void GPIO_Pullup_Enable(PIN_ID Pin)
{
	CLR_BIT(SFIOR,PUD);
	GPIO_WritePin(Pin,HIGH);

}
void GPIO_Pullup_Disable()
{
	SET_BIT(SFIOR,PUD);
}


