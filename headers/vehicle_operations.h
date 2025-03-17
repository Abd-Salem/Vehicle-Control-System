/******************************************************************************
 *
 * File Name: defines.h
 *
 * Description: types for Vehicle Control system
 *
 * Author: Abdallah Ashraf
 *
 *******************************************************************************/

#ifndef MYFUN_H_
#define MYFUN_H_

#include "definitions.h"

/*
 * description:
 * structure of variables that represent the states of system
 * */
typedef struct {
	bool Eng_state;
	bool AC;
	bool eng_temp_con_state;
} VecState;

/*
 * description:
 * structure of variables that represent the reading of sensors
 *
 * */

typedef struct {
	uint32 room_temp;
	uint32 eng_temp;
	uint32 vec_speed;
} VecVar;

/* structures that will used in another file  */
extern VecVar g_variables; //global structure for system changes according to sensors in the system

extern VecState g_statements; //global structure readings and states of the system

extern uint8 g_input;  //global variable that get the input from the user

/*
 *  description:
 * 	function that check states of the parts of the vehicle system
 * 	print the states to the user
 */
noret printStates(VecVar *var, VecState *state);

/*
 * description:
 * function called when the user turn on the engine
 *
 */
noret turnOnOptions(noarg);

/*
 * description:
 * get the color of the traffic lights
 * checking the color and taking an action on the vehicle speed
 *
 */
noret trafficLights(VecVar *var);

/*
 * description:
 * get the temperature degree value of the room
 * take action according to the degree
 *
 */
noret roomTempCheck(VecVar *var, VecState *state);

/*
 * description:
 * getting engine temperature value
 * take action according to the value
 *
 */
noret engTempCheck(VecVar *var, VecState *state);

/*
 * description:
 * specific condition for vehicle speed
 * take an action according to a specific speed
 */
noret vecSpeedOp(VecVar *var, VecState *state);

/*
 * description:
 * checking the states and handling it according to shutdown option
 */
noret shutdownEng(VecVar *var, VecState *state);

/*
 * description:
 * if user turn on the engine this function is called
 * complete the turn on state with the user
 *
 */
noret turnOnStates(noarg);

/*
 * description:
 * Print some choices for user
 */
noret printChoices(noarg);

#endif /* MYFUN_H_ */
