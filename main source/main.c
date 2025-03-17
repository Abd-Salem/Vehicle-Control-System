/******************************************************************************
 *
 * File Name: mainprog.c
 *
 * Description: source file of Vehicle Control system
 *
 * Author: Abdallah Ashraf
 *
 *******************************************************************************/

#include "../headers/vehicle_operations.h"

/* definition */
#define Quit_System   return 0

int main(void) {

	/* initial values for temperature parameters*/
	g_variables.eng_temp = 50;
	g_variables.room_temp = 25;

	while (1) {
		/*system options for user*/
		printChoices();
		printStates(&g_variables, &g_statements);  //print states of the vehicle

		/* get option that the user chose and making sure that the user choose the right option
		 * if user chooses c system will shutdown.
		 * if user chooses b engine will be stopped if it runs
		 * if user chooses a engine will be turned on if it is stopped and show to the user turn on engine options
		 *  */

		scanf(" %c", &g_input);
		while (g_input != 'a' && g_input != 'b' && g_input != 'c') {
			printf("Please, enter right option!!\n");
			scanf(" %c", &g_input);
		}
		if (g_input == 'c')
			Quit_System;
		else if (g_input == 'b')
			shutdownEng(&g_variables, &g_statements);
		else if (g_input == 'a')
			turnOnStates(); //states and options when user choose to turn on the engine

	}
	return 0;
}
//END of the file
