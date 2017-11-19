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
	STACK route; //stack holding the route information
	createStack(&route);

	//creating initial junction
	root = malloc(sizeof(jct));
	cityListRoot = malloc(sizeof(jct));
	start = malloc(sizeof(city));
	end = malloc(sizeof(city));
	root->nextCity = NULL;
	root->nextJCT = NULL;
	cityListRoot = root;

	//run functions
	createMap(root);
        printf("\n|-------------------------------------------------|\n");
	printf("|Portland Route Finder                            |\n");
	printf("|Given a starting city and a destination,         |\n");
	printf("|this program will return a route between them.   |\n");
        printf("|-------------------------------------------------|\n\n");
        input(root, start, end, cityListRoot);
	pathSearch(root, start, end, &route); //find route from start to end
	printRoute(route, start, end);
}
