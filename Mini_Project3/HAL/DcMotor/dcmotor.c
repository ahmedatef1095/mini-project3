
#include "dcmotor.h"

#include "../../mcal/gpio/gpio.h"
#include "../../mcal/pwm/pwm.h"


void DcMotor_init(void)
{
	/*set PIN_IN1 and PIN_IN2 as OUTPUT pins*/
	GPIO_setupPinDirection(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,PIN_OUTPUT);

	/*set PIN_IN1 and PIN_IN2 Low so Motor is stop at the beginning */
	GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);

}
void DcMotor_rotate(DcMotor_State state,uint8 speed)
{
	switch(state)
	{
		case(DcMotor_STOP):  /*DC Motor Stop*/
					GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
					GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
		break;

		/*DC Motor rotate*/
		case(DcMotor_CLOCKWISE):   /*DcMotor rotate CLOCKWISE*/
					GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
					GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_HIGH);
		break;

		case(DcMotor_ANTI_CLOCKWISE):	/*DcMotor rotate ANTI CLOCKWISE*/
					GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_HIGH);
					GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
		break;
	}

	/*covert speed to duty cycle*/
	uint8 dutyCycle =((speed/100)*255);   //to Avoid overflow
	/*call PWM function to determine the speed */
	Timer0_PWM_init(dutyCycle);

}
