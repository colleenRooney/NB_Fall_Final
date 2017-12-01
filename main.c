#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "definitions.h"
#include "functions.h"

void main(void)
{
	//variables
	city *start, *end; //s is starting city pointer, e is ending city pointer
	junction *root;
	STACK *route; //stack holding the route information
	route = malloc(sizeof(STACK));
	createStack(route);
	char cont = 'y'; //check whether to loop program
	float milesTotal; //float variable for the total trip miles

	//creating initial junction
	root = malloc(sizeof(junction));
	start = malloc(sizeof(city));
	end = malloc(sizeof(city));
	root->nextCity = NULL;
	root->nextJunction = NULL;
	createMap(root);

	//program introduction for user
	printf("\n|-----------------------------------------------------------------|\n");
	printf("|Portland Route Finder                                 _____      |\n");
	printf("|Given a starting city and a destination,          __ /__||_\\__   |\n");
	printf("|this program will return a route between them.   |_( )____( )_|  |\n");
	printf("|-----------------------------------------------------------------|\n\n");

	//run functions
	while(cont != 'n')
	{
		userInput(root, start, end);
		makePath(root, start, end, route, &milesTotal);
		printRoute(route, start, end, &milesTotal);
		while(1)
		{
			printf("Check another route(y/n)? ");
			cont = getchar();
			getchar();
			if(cont == 'y' || cont == 'n') break;
		}
	}
}
