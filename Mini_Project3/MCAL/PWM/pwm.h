
#ifndef PWM_H_
#define PWM_H_

#include "../../lib/std_types.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * Setup Timer0 at Normal Mode
 * Timer0 will be used with pre-scaler F_CPU/8
 * Duty Cycle can be changed be update the value in
 * The Compare Register
 */
void Timer0_PWM_init(uint8 duty_cycle);


#endif
