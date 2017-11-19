#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "stack.h"
#include "func.h"

void main(void)
{
	//variables
	city *start, *end; //s is starting city pointer, e is ending city pointer
	jct *root, *cityListRoot;
	STACK *route; //stack holding the route information
	route = malloc(sizeof(STACK));
	createStack(route);
	char cont = 'y'; //check whether to loop program
	//creating initial junction
	root = malloc(sizeof(jct));
	cityListRoot = malloc(sizeof(jct));
	start = malloc(sizeof(city));
	end = malloc(sizeof(city));
	root->nextCity = NULL;
	root->nextJCT = NULL;
	cityListRoot = root;
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
		input(root, start, end, cityListRoot);
		makePath(root, start, end, route);
		printRoute(route, start, end);
		printf("Check another route(y/n)? ");
		cont = getchar();
		getchar();
	}
}
