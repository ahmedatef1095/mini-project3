#include "DcMotor.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/PWM/pwm.h"

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
		/*DcMotor stop*/
		case(DcMotor_STOP):
			 GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
			 GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
		break;
		/*DcMotor rotate CLOCKWISE*/
		case(DcMotor_CLOCKWISE):
			GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_LOW);
			GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_HIGH);
		break;
		/*DcMotor rotate ANTI CLOCKWISE*/
		case(DcMotor_ANTI_CLOCKWISE):
			GPIO_writePin(DcMotor_IN1_PORT_ID,DcMotor_IN1_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(DcMotor_IN2_PORT_ID,DcMotor_IN2_PIN_ID,LOGIC_LOW);
		break;
	}
	/*covert speed to duty cycle*/
	uint8 dutyCycle =((speed*256)/100)-1;
	/*call PWM function to determine the speed */
	Timer0_PWM_Init(dutyCycle);
}
