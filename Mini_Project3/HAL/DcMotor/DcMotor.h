
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "../../LIB/std_types.h"


#define DcMotor_IN1_PORT_ID                 PORTB_ID
#define DcMotor_IN1_PIN_ID                  PIN0_ID

#define DcMotor_IN2_PORT_ID                 PORTB_ID
#define DcMotor_IN2_PIN_ID                  PIN1_ID


typedef enum
{
	DcMotor_STOP=0,
	DcMotor_CLOCKWISE,
	DcMotor_ANTI_CLOCKWISE,
}DcMotor_State;

void DcMotor_init(void);
void DcMotor_rotate(DcMotor_State state,uint8 speed);

#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
