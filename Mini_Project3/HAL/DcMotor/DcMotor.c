#include "DcMotor.h"

#include "../../MCAL/GPIO/GPIO.h"

void DcMotor_init(void)
{
 GPIO_setupPinDirection(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,PIN_OUTPUT);
 GPIO_setupPinDirection(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,PIN_OUTPUT);

 GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
 GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
 /* Motor is stop at the beginning */
}
void DcMotor_rotate(DcMotor_State state,uint8 speed)
{
	switch(state)
	{
	case(DcMotor_STOP):
		 GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
		 GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
	break;
	case(DcMotor_CLOCKWISE):
		GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_HIGH);
		switch(speed)
		{
		default:
			GPIO_writePin(DcMotor_IN2_PORT_ID,PIN3_ID,LOGIC_HIGH);
			break;
		}
	break;
	case(DcMotor_ANTI_CLOCKWISE):

		GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
		switch(speed)
		{
		default:
			GPIO_writePin(DcMotor_IN2_PORT_ID,PIN3_ID,LOGIC_HIGH);
			break;
		}
	break;
	}

}
