#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
#include "utility.h"
#include "stack.h"

/*************************************************************
*createMap
* loads in map from file
* map must be north most cities -> south most cities
* a junction Hwy_26 seperator is needed
*************************************************************/
void createMap(junction *root)
{
	//variables
	char cityName[MAX_LENGTH];
	char directionIndicator[MAX_LENGTH];
	city *newCity, *lastcity;
	junction *lastJunction, *currentJunction;
	int firstCity = 0;
	float cityMiles;
	FILE *fp;

	for(int i = 0; i < FILES_TO_READ; i++)
	{
		//opening proper file
		if(i == 0) fp = fopen("north", "r");
		else if(i == 1) fp = fopen("south", "r");
		else if(i == 2) fp = fopen("east", "r");
		else if(i == 3) fp = fopen("west", "r");

		//create junction node
		fgets(directionIndicator, MAX_LENGTH, fp);
		standardizeInput(directionIndicator);
		decap(&directionIndicator[0]);

		currentJunction = malloc(sizeof(junction));
		currentJunction->nextJunction = NULL;
		currentJunction->nextCity = NULL;
		strcpy(currentJunction->direction, directionIndicator);

		if(i == 0) //points root to first junction
		{
			root->nextJunction = currentJunction;
		}
		else //set last junction to current junction
		{
			lastJunction->nextJunction = currentJunction;
		}

		lastJunction = currentJunction; //changes junction to last junction

		//reading city names from file into city nodes
		fgets(cityName, MAX_LENGTH, fp);
		breakupInput(cityName, &cityMiles);

		while(strcmp(cityName, "*") != 0) // The * denotes end of file
		{
			newCity = malloc(sizeof(city));
			newCity->next = NULL;
			newCity->prev = NULL;
			strcpy(newCity->name, cityName);
			newCity->miles = cityMiles;

			if(firstCity == 0)//connecting first city to the junction
			{
				currentJunction->nextCity = newCity;
				firstCity++;
			}
			else//for rest of cities in list
			{
				lastcity->next = newCity;
				newCity->prev = lastcity;
			}

			lastcity = newCity;
			fgets(cityName, MAX_LENGTH, fp);
			breakupInput(cityName, &cityMiles);
		}

		firstCity = 0; //reseting variable for next map read
		fclose(fp);
	}

	lastJunction->nextJunction = root->nextJunction; //connects junction loop
}

/*************************************************************************
*citySearch
* Takes in a city, finds it in the map, and points a pointer to it
* returns 1 if the city is in the map, 0 if it is not
**************************************************************************/
int citySearch(char name[], city *c, junction *root)
{
	//variables
	char initialCity[MAX_LENGTH]; // starting city
	city *search; //city to be searched
	junction *currentJunction; //current junction node

	//setting break condition
	currentJunction = root->nextJunction;
	search = currentJunction->nextCity;
	strcpy(initialCity, search->name);

	while(1)
	{
		if(strcmp(name, search->name) == 0) //checks for break condition
		{
			strcpy(c->name, search->name); //sets incoming pointer to the current city node
			c->next = search->next;
			c->prev = search->prev;
			c->miles = search->miles;
			strcpy(c->direction, currentJunction->direction);
			return 1;
		}

		if(search->next == NULL) //if at the end of a branch go to next junction branch
		{
			currentJunction = currentJunction->nextJunction;
			search = currentJunction->nextCity;
			if(strcmp(search->name, initialCity) == 0) //checks to see if at original branch, if so exits
			{
				printf(RED "City does not exist in map.\n" COLOR_RESET);
				return 0;
			}
		}
		else search = search->next; //traverses the list
	}
}

/******************************************
*makePath
* determines state from direction and
* position values of start and end and
* loads a stack with the path
******************************************/
void makePath(junction *root, city *start, city *end, STACK *route, float *milesTotal)
{
	junction *currentJunction = root->nextJunction;
	city *currentCity;
	currentCity = end;
	Push(route, currentCity->name); //push end city onto stack

	if(strcmp(start->name, "I-5 Hwy-26 Junction") == 0) strcpy(start->direction, end->direction);
	else if(strcmp(end->name, "I-5 Hwy-26 Junction") == 0) strcpy(end->direction, start->direction);

	while(strcmp(currentJunction->direction, start->direction) != 0)//finding the start junction
	{
		currentJunction = currentJunction->nextJunction;
	}
	if(strcmp(start->direction, end->direction) != 0) //cities on different branches
	{
		*milesTotal = start->miles + end->miles;
		while(currentCity->prev != NULL)
		{
			currentCity = currentCity->prev;
			Push(route, currentCity->name);
		}

		Push(route, "junction");
		currentCity = currentJunction->nextCity;

		while(strcmp(currentCity->name, start->name) != 0)
		{
			Push(route, currentCity->name);
			currentCity = currentCity->next;
		}

		Push(route, currentCity->name);
	}

	else if(start->miles > end->miles) //same branch, start is further down than end
	{
		*milesTotal = start->miles - end->miles;

		if(strcmp(end->name, "I-5 Hwy-26 Junction") == 0)
		{
			currentCity = currentJunction->nextCity;
			Push(route, currentCity->name);
		}
		while(strcmp(currentCity->name, start->name) != 0)
		{
			currentCity = currentCity->next;
			Push(route, currentCity->name);
		}
	}

	else //start is further up than end
	{
		*milesTotal = end->miles - start->miles;
		while(strcmp(currentCity->name, start->name) != 0)
		{
			if(currentCity->prev == NULL)
			{
				Push(route, start->name);
				break;
			}
			currentCity = currentCity->prev;
			Push(route, currentCity->name);
		}
	}

	return;
}

/********************************************
*printCityList
* Prints our a list of available cities
*********************************************/
void printCityList(junction *root)
{
	city *currentCity;
	junction *currentJunction;
	currentJunction = root->nextJunction;
	currentCity = currentJunction->nextCity;
	char name[MAX_LENGTH];
	int i, j, k;
	int length; //holds string length to help format printing
	int level = 0; //level determines how many cities down we need to move to print
	int nullCount = 0; //each time our next city is null increment, when all 4 branches are null return

	for(j = 0; j < FILES_TO_READ; j++)
	{
		strcpy(name, currentJunction->direction);
		capitalize(&name[0]);
		length = strlen(name);
   		printf("%s", name);
   		for(i = 0; i < (MAX_LENGTH - length); i++) printf(" "); //provides even spacing by accounting for name length
			currentJunction = currentJunction->nextJunction;
	}
	printf("\n--------------------------------------------------------------------------------------------\n");

	while(nullCount != FILES_TO_READ)
	{
		nullCount = 0;
		currentJunction = root->nextJunction;
		currentCity = currentJunction->nextCity;
		strcpy(name, currentCity->name);
		for(i = 0; i < FILES_TO_READ; i++) //prints out one name per branch
		{
			for(j = 0; j < level; j++) //moves down the city list to find a cityat a given level
			{
				if(currentCity->next != NULL)
				{
					currentCity = currentCity->next;
					strcpy(name, currentCity->name);
				}
				else //once the branch is null, increment null counter and make a blank string to print
				{
					strcpy(name, " ");
					nullCount++;
					break;
				}
			}
			length = strlen(name);
       		printf("%s", name);
	        for(k = 0; k < (MAX_LENGTH - length); k++) printf(" ");
			currentJunction = currentJunction->nextJunction;
			currentCity = currentJunction->nextCity;
			strcpy(name, currentCity->name);
		}
		printf("\n");
		level++;
	}
}

/********************************************
*input
* Get user input, and set start
* and ending city pointers
*********************************************/
void userInput(junction *root, city *start, city *end) //root of the map, pointer to the starting city, pointer to the ending city
{
	char startingCity[MAX_LENGTH], endingCity[MAX_LENGTH];
	int junctionStart = 0;
	int junctionEnd = 0;

	while(1) //get valid starting city
	{
		printf("Enter the starting city(or 'citylist' for a list of available cities): ");
		fgets(startingCity, MAX_LENGTH, stdin);
		standardizeInput(startingCity);

		if(strcmp(startingCity, "Citylist") == 0) //prints out a list of cities in the map
		{
			printCityList(root);
		}
		else if(strcmp(startingCity, "Junction") == 0 || strcmp(startingCity, "I5") == 0 || strcmp (startingCity, "Hwy 26") == 0)
		{
			strcpy(start->name, "I-5 Hwy-26 Junction");
			start->miles = 0;
			junctionStart = 1;
			break;
		}
		else if(citySearch(startingCity, start, root) == 1) //if city exists in the map sets starting city and returns
		{
			break;
		}
	}
	while(1) //get valid ending city
	{
		printf("Enter the destination city(or 'citylist' for a list of available cities): ");
		fgets(endingCity, MAX_LENGTH, stdin);
		standardizeInput(endingCity);
		int compareCity = 0;

		if(strcmp(endingCity, "Citylist") == 0)//prints out a list of cities in the map
		{
			printCityList(root);
		}
		else if(strcmp(endingCity, "Junction") == 0 || strcmp(endingCity, "I5") == 0 || strcmp (endingCity, "Hwy 26") == 0)
		{
			strcpy(end->name, "I-5 Hwy-26 Junction");
			end->miles = 0;
			junctionEnd = 1;
			if(!junctionStart) break;
		}

		if(strcmp(startingCity, endingCity) == 0) compareCity = 1;
		if(junctionStart && junctionEnd) compareCity = 1;
		
		if(compareCity) //starting and ending cities cannot be the same
		{
			junctionEnd = 0;
			printf(RED "You're already there. Try another destination.\n" COLOR_RESET);
		}
		else if(citySearch(endingCity, end, root) == 1)//checks if city exists in the map, if true sets the ending city and returns
		{
			break;
		}
	}
}

/**********************************
*swapDirection
* swaps cardinal directions
***********************************/
void swapDirection(char currentDirection[MAX_LENGTH])
{
	if(strcmp(currentDirection, "north") == 0) strcpy(currentDirection, "south");
	else if(strcmp(currentDirection, "south") == 0) strcpy(currentDirection, "north");
	else if(strcmp(currentDirection, "east") == 0) strcpy(currentDirection, "west");
	else if(strcmp(currentDirection, "west") == 0) strcpy(currentDirection, "east");
}

/****************************************
*printRoute
* Pops elements from a stack and prints.
******************************************/
void printRoute(STACK *route, city *start, city *end, float *milesTotal)
{
	city temp = Pop(route);
	char currentDirection[MAX_LENGTH];
	char highway[MAX_LENGTH];
	float costTotal = *milesTotal * COST_PER_MILE;

	strcpy(currentDirection, start->direction);

	if(strcmp(start->direction, "north") == 0 || strcmp(start->direction, "south") == 0) strcpy(highway, "Interstate 5");
	else if(strcmp(start->direction, "east") == 0 || strcmp(start->direction, "west") == 0) strcpy(highway, "Highway 26");

	if(strcmp(start->direction, end->direction) != 0 || start->miles > end->miles) //if moving towards to the junction
	{
		swapDirection(currentDirection); //correct for direction of movement
	}
	printf("\nHeading %s out of %s on %s...\n", currentDirection, temp.name, highway);

	while(strcmp(temp.name, end->name) != 0)
	{
		temp = Pop(route);
		if(strcmp(temp.name, "junction") != 0 && strcmp(temp.name, end->name) != 0)  //don't print junction or last element
		{
			printf("passing %s...\n", temp.name);
		}
		else if(strcmp(temp.name, "junction") == 0) //moving between branches, might change onto different highway
		{
			if(strcmp(end->direction, currentDirection) == 0) //if staying on the same highway
    		{
        		printf("continuing %s on %s...\n", currentDirection, highway);
    		}
    		else //turning onto new highway
    		{
        		if(strcmp(highway, "Interstate 5") == 0) strcpy(highway, "Highway 26");
        		else strcpy(highway, "Interstate 5");
        		printf("turning %s onto %s...\n", end->direction, highway);
    		}
		}
	}

	printf("arrived at %s.\n", temp.name);
	printf("Miles travelled: %.2f\n",*milesTotal);
	printf("Total Cost of Trip: $%.2f\n\n",costTotal);
	return;
}
