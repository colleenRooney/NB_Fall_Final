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
	printf("Portland Path Finder\n");
	printf("Enter the city you're starting from and the city you're trying to get to and get the path between them.\n");
	input(root, start, end, cityListRoot);
	makePath(root, start, end, route);
//	pathSearch(root, start, end, &route); //find route from start to end
	printRoute(route, start, end);
}
