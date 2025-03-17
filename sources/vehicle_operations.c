 /******************************************************************************
 *
 * File Name: myfun.h
 *
 * Description: source file for functions of the Vehicle Control system
 *
 * Author: Abdallah Ashraf
 *
 *******************************************************************************/

#include <stdio.h>  // standard lib.
#include "../headers/vehicle_operations.h"

/* definition for engine temperature controller if used or not as hardware in the vehicle*/
#define WITh_ENGINE_TEMP_CONTROLLER  FALSE


/*structures of variables for system changes and states*/
VecVar g_variables;
VecState g_statements;

uint8 g_input; // user input



/*
 * description:
 * function to print some choices fro user on the screen
 *
 */
noret printChoices(noarg){
	printf("a- Turn ON the Vehicle Engine\n");
	printf("b- Turn OFF the Vehicle Engine\n");
	printf("c- Quit the System\n");
}

/*
 *  description:
 * 	function that check states of the parts of the vehicle system
 * 	print the states to the user
 */
noret printStates(VecVar *var,VecState *state)
{
	/* some checks and prints according to the states*/

	if(state->Eng_state == ON)
	{
		printf("Engine State: ON\n");

	}
	else if(state->Eng_state == OFF)
	{
		printf("Engine State: OFF\n");
	}

	if(state->AC == ON)
	{
		printf("AC: ON\n");
	}
	else if(state->AC == OFF)
	{
		printf("AC: OFF\n");
	}

	printf("Vehicle Speed: %d\n",var->vec_speed);

	printf("Room Temperature: %d\n",var->room_temp);

/*preprossor directive that check if there is engine controller in the vehicle or not*/
#if(WITH_ENGINE_TEMP_CONTROLLER == TRUE)

	if(state->eng_temp_con_state == ON)
	{
		printf("Engine Temperature State: ON\n");
	}
	else if(state->eng_temp_con_state == OFF)
	{
		printf("Engine Temperature State: OFF\n");
	}

	printf("Engine Temperature: %d\n",var->eng_temp);
#endif
}


/*
 * description:
 * function called when the user turn on the engine
 *
 * */
noret turnOnOptions(noarg)
{
	/*print options*/
	printf("a- Turn Off Engine\n");
	printf("b- Set the traffic light\n");
	printf("c- Set the room temperature(temperature sensor)\n");


	/*preprocessor directive that check if there is engine controller in the vehicle or not*/
#if(WITH_ENGINE_TEMP_CONTROLLER == TRUE)
	printf("d- Set engine temperature(engine temperature sensor)\n");
#endif
}


/*
 * description:
 * get the color of the traffic lights
 * checking the color and taking an action on the vehicle speed
 *
 **/
noret trafficLights(VecVar *var)
{
	scanf(" %c",&g_input); //getting the color from user

	/* being sure that the user enter the required color*/
	while(g_input != 'g' && g_input != 'o' && g_input != 'r')
	{
		printf("Enter right option!!\n");
		scanf(" %c",&g_input);
	}

	/*value condition with different responses from the system*/
	if(g_input == 'g')
	{
		var->vec_speed = 100;
	}
	else if(g_input == 'o')
	{
		var->vec_speed = 30;
	}
	else if(g_input == 'r')
	{
		var->vec_speed = 0;
	}
}



/*
 * description:
 * get the temperature degree value of the room
 * take action according to the degree
 *
 */
noret roomTempCheck(VecVar *var,VecState *state)
{

	scanf("%d",&var->room_temp);  //reading the value of the temperature degree

	/*value condition with different responses by the system */
	if(var->room_temp < 10)
	{
		var->room_temp = 20;
		state->AC = ON;
	}
	else if(var->room_temp > 30)
	{
		var->room_temp = 20;
		state->AC = ON;
	}
	else
	{
		state->AC = OFF;
	}

}


 /*preprocessor directive that check if there is engine controller in the vehicle or not*/
#if(WITh_ENGINE_TEMP_CONTROLLER == TRUE)

/*
 * description:
 * getting engine temperature value
 * take action according to the value
 *
 * */

noret eng_temp_check(VecVar *var,VecState *state)
{
	scanf("%d",&var->eng_temp);  //getting the temperature value of the engine

	if(var->eng_temp < 100)
	{
		state->eng_temp_con_state = ON;
		var->eng_temp = 125;
	}
	else if(var->eng_temp > 150)
	{
		state->eng_temp_con_state = ON;
		var->eng_temp = 125;
	}
	else
	{
		state->eng_temp_con_state = OFF;
	}
}
#endif


/*
 * description:
 * specific condition for vehicle speed
 * take an action according to a specific speed
 */

noret vecSpeedOp(VecVar *var,VecState *state)
{
	/* speed check */
	if(var->vec_speed == 30)
	{
		/*the action */
		state->AC = ON;
		var->room_temp = (var->room_temp * (float)5/4) + 1;

 /*preprocessor directive that check if there is engine controller in the vehicle or not*/
#if(WITH_ENGINE_TEMP_CONTROLLER == TRUE)
		state->eng_temp_con_state = ON;
		var->eng_temp = (var->eng_temp * (float)5/4) + 1;
#endif
	}
}


/*
 * description:
 * checking the states and handling it according to shutdown option
 */
noret shutdownEng(VecVar *var,VecState *state)
{
	/* checks */
	if(state->Eng_state == ON)
		state->Eng_state = OFF;

	if(state->AC == ON)
		state->AC = OFF;

	if(state->eng_temp_con_state == ON)
		state->eng_temp_con_state = OFF;

	if(var->vec_speed != 0)
		var->vec_speed = 0;

	if(var->eng_temp != 50)
		var->eng_temp = 50;

	if(var->room_temp != 25)
		var->room_temp = 25;
}



/*
 * description:
 * if user turn on the engine this function is called
 * complete the turn on state with the user
 *
 */
noret turnOnStates(noarg)
{
	while(1)
	{
		/* turning on engine */
		if(g_statements.Eng_state == OFF)
			g_statements.Eng_state = ON;

		vecSpeedOp(&g_variables,&g_statements); //speed checking


		turnOnOptions();  //print options when engine is turned on

		printStates(&g_variables,&g_statements);  //state of the parts of the system

		scanf(" %c",&g_input);   //getting the choice from the user

		/* making sure that the user entere the right option*/

		while(g_input != 'a' && g_input != 'b' && g_input != 'c' && g_input != 'd')
		{
			printf("Enter right option!!\n");
			scanf(" %c",&g_input);
		}

		/* checking and taking action */

		if(g_input == 'a')
		{
			shutdownEng(&g_variables,&g_statements);
			break;
		}
		else if(g_input == 'b')
		{
			trafficLights(&g_variables);
		}
		else if(g_input == 'c')
		{
			roomTempCheck(&g_variables,&g_statements);
		}

	/*preprocessor directive that check if there is engine controller in the vehicle or not*/
#if(WITh_ENGINE_TEMP_CONTROLLER == TRUE)
		else if(g_input == 'd')
		{
			eng_temp_check(&g_variables,&g_statements);
		}
#endif
	}
}
