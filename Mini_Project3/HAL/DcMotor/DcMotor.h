
#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "../../lib/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DcMotor_IN1_PORT_ID                 PORTB_ID
#define DcMotor_IN1_PIN_ID                  PIN0_ID

#define DcMotor_IN2_PORT_ID                 PORTB_ID
#define DcMotor_IN2_PIN_ID                  PIN1_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	DcMotor_STOP=0,
	DcMotor_CLOCKWISE,
	DcMotor_ANTI_CLOCKWISE,
}DcMotor_State;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Setup DcMotor configuration.
 */
void DcMotor_init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value
 */
void DcMotor_rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
