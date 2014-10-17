/*
 * s1.c
 *
 *  Created on: Jan 9, 2010
 *      Author: arun
 */

#include <stdio.h>
#include <stdlib.h>

//Max numbr of states and events
int max_states = 3;
int max_events = 4;
//Max handlers associated with each state transition
#define MAX_HANDLERS 4
#define UNSUPPORTED_EVENT -1
#define INVALID_EVENT -2

//declare the func pointer type
typedef int (*func_pointer)();

//Structure to store the nextState and handlers that has to be executed
typedef struct {
	int nextState;

	int no_of_handlers;

	//this is basically an array of handlers for this transition
	func_pointer *handlers;

} Transition;

//Now define 2d array of Transition states ie max_states X max_events
Transition **states;
int cur_state;

//Following are the handler functions
int handler0(){
	printf("Handler 0\n");
	return 0;
}

int handler1(){
	printf("Handler 1\n");
	return 0;
}

int handler2(){
	printf("Handler 2\n");
	return 0;
}

int handler3(){
	printf("Handler 3\n");
	return 0;
}

int applyStateTransitionRule(int event){

	int next;
	int noOfHandlers;
	int ret,i;

	//Check if the event is valid
	if (event<0 || event >=max_events)
		return INVALID_EVENT;

	next = states[cur_state][event].nextState;
	noOfHandlers = states[cur_state][event].no_of_handlers;

	//First check if  the cur state is valid for this event
	if (next == -1)
		return UNSUPPORTED_EVENT;

	//Run the handlers, and if any one of them fails, then we return error;
	if (noOfHandlers > 0)
		printf("\nExecuting the following handlers\n");
	else
		printf("\nNo Handlers available for this transition.\n");

	for (i = 0; i < noOfHandlers; ++i) {
		ret = states[cur_state][event].handlers[i]();
		//Failed
		if (ret != 0)
			return ret;
	}
	cur_state = next;
	return 0;
}

int main(int argc, char **argv) {

	int i = 0,j,k,ret;
	char ch;

	//Array of function pointers for adding handlers
	func_pointer handlers[MAX_HANDLERS];

	handlers[0]=handler0;handlers[1]=handler1;handlers[2]=handler2;handlers[3]=handler3;

	states = (Transition **)malloc(sizeof(Transition*) * max_states);
	for (i = 0; i < max_states; ++i) {
		states[i] = (Transition*)malloc(sizeof(Transition)*max_events);
		//loop to populate the structure with some default
		for (j = 0; j < max_events; ++j) {
			//-1 implies this is an invalid transition
			states[i][j].nextState = -1;

			states[i][j].no_of_handlers = 0;
			states[i][j].handlers = NULL;
		}
	}

	//Now wire the transitions to each state, some FSM
	for (i = 0; i < max_states; ++i) {
		for (j = 0; j < max_events; ++j) {
			//If the state and event are same then Mark it as an invalid Transition
			if(i == j) {
				states[i][j].nextState = -1;
				continue;
			}
			states[i][j].nextState = (i+j)%max_states;
			states[i][j].no_of_handlers = (i+j)%(MAX_HANDLERS);
			if (states[i][j].no_of_handlers > 0)
				states[i][j].handlers = (func_pointer*)malloc(sizeof(func_pointer) * states[i][j].no_of_handlers);
			for (k = 0; k < states[i][j].no_of_handlers; ++k) {
				states[i][j].handlers[k]=handlers[k];
			}
		}
	}
	printf("\nMax States = %d, MAX Events = %d, Max handlers = %d\n\n",max_states,max_events,MAX_HANDLERS);

	//Start with some initial state < max_states
	cur_state = 0;
	printf ("Starting the fsm at Initial State = %d\n",cur_state);


	//Now keep running a loop for random events and see the output
	do {
		i = rand()%max_events;
		printf("\nSending event %d to State %d\n",i,cur_state);
		ret = applyStateTransitionRule(i);
		if (ret == UNSUPPORTED_EVENT) {
			printf("\nThis event is not supported for this state\n");
		} else if (ret == 0) {
			printf("\nSuccessfully transitioned to Next State = %d\n",cur_state);
		} else {
			printf("\nInvalid Event\n");
		}

		printf("\n*************************************************************\n");
		printf("\nDo you want to Continue?[y] ");
		ch = getchar();

	}while(ch != 'n' && ch != 'N');

	return 0;
}
