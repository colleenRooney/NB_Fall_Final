#define FILES_TO_READ 2
#define MAX_NAME 20

/*********************************************\
*isaLetter
* returns true if character is a letter
\**********************************************/
int isaLetter(char letter) //if character is a letter return 1, else return 0
{
	if(((letter <= 122) && (letter >= 97)) || ((letter <= 90) && (letter >= 65)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*********************************************\
*isaSpace
* returns true if character is a space
\**********************************************/
int isaSpace(char letter)
{
	if(letter == 32) return 1;
	else return 0;
}

/*********************************************\
*decap
* decaps input if input is uppercase
\**********************************************/
void decap(char *letter) //function returns lowercase equivalent of uppercase letter
{
	if((*letter <= 90) && (*letter >= 65)) 
	{
		*letter = *letter + 32;
	}
	return;
}
 
/*********************************************\
*capitalize
* capitalizes input if input is lowercase
\**********************************************/
void capitalize(char *letter) //function returns uppercase equivalent of lowercase letter
{
	if((*letter <= 122) && (*letter >= 97))
		{
			*letter = *letter - 32;
		}
	return;
}

/*********************************************\
*sanitizeInput
* modifies a string into a standard format
\**********************************************/
void sanitizeInput(char input[])
{
	int length = strlen(input);

	for(int i = 0; i < length; i++)
	{
		if(input[i] == '\n')
		{
			input[i] = '\0'; //terminate string
		}
		else if(i == 0 || isaSpace(input[i-1])) //if first letter or new word
		{
			capitalize(&input[i]);
		}
		else if(isaSpace(input[i]) && !isaLetter(input[i+1])) //if character is a space without a following letter
		{
			input[i]='\0'; //terminate string
		}
		else
		{
			decap(&input[i]);
		}
	}
}

/*************************************************************
*createMap
* loads in map from file
* map must be north most cities -> south most cities
* a junction Hwy_26 seperator is needed
*************************************************************/
void createMap(jct *root)
{
	//variables
	char cityName[MAX_NAME];
	char directionIndicator[10];
	city *newCity, *lastcity;
	jct *lastJunction, *currentJunction, *firstjct;
	int positionIndicator = 0;
	int firstCity = 0;

	FILE *fp;

	for(int i = 0; i < FILES_TO_READ; i++)
	{
		//opening proper file
		if(i == 0) fp = fopen("north", "r");
		else if(i == 1) fp = fopen("south", "r");
		else if(i == 2) fp = fopen("east", "r");
		else if(i == 3) fp = fopen("west", "r");

		//create junction node
		fgets(directionIndicator, 10, fp);
		sanitizeInput(directionIndicator);
		decap(&directionIndicator[0]);
		currentJunction = malloc(sizeof(jct));
		currentJunction->nextJCT = NULL;
		currentJunction->nextCity = NULL;
		strcpy(currentJunction->direction, directionIndicator);

		if(i == 0) //points root to first junction
		{
			root->nextJCT = currentJunction;
			firstjct = currentJunction;
		}
		else //set last junction to current junction
		{
			lastJunction->nextJCT = currentJunction;
		}
		lastJunction = currentJunction; //changes junction to last junction

		//reading city names from file into city nodes
		fgets(cityName, MAX_NAME, fp);
		sanitizeInput(cityName);
		while(strcmp(cityName, "*") != 0) // The * denotes end of file
		{
			positionIndicator++;
			newCity = malloc(sizeof(city));
			newCity->next = NULL;
			newCity->prev = NULL;
			newCity->position = positionIndicator;
			strcpy(newCity->name, cityName);
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
			fgets(cityName, MAX_NAME, fp);
			sanitizeInput(cityName);
		}
		positionIndicator = 0; //reseting variables for next read
		firstCity = 0;
		fclose(fp);
	}
	lastJunction->nextJCT = firstjct;
}

/*************************************************************************
*citySearch
* Takes in a city, finds it in the map, and points a pointer to it
* returns 1 if the city is in the map, 0 if it is not
**************************************************************************/
int citySearch(char name[], city *c, jct *root)
{
	//variables
	char initialCity[MAX_NAME]; // starting city
	city *search; //city to be searched
	jct *currentJunction; //current junction node
<<<<<<< HEAD

	//setting break condiiton
=======
	//setting break condition
>>>>>>> 3a8849a8d8b879db81ef2ec04cd518349be34323
	currentJunction = root->nextJCT;
	search = currentJunction->nextCity;
	strcpy(initialCity, search->name);

	while(1)
	{
		if(strcmp(name, search->name) == 0) //checks for break condition
		{
			strcpy(c->name, search->name); //sets incoming pointer to the current city node
			c->next = search->next;
			c->prev = search->prev;
			c->position = search->position;
			strcpy(c->direction, currentJunction->direction);
			return 1;
		}

		if(search->next == NULL) //if at the end of a branch go to next junction branch
		{
			currentJunction = currentJunction->nextJCT;
			search = currentJunction->nextCity;
			if(strcmp(search->name, initialCity) == 0) //checks to see if at original branch, if so exits
			{
				printf("City does not exist in map.\n");
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
void makePath(jct *root, city *start, city *end, STACK *route)
{
	jct *currentJunction = root->nextJCT;
	city *currentCity;
	currentCity = end;
	Push(route, currentCity->name); //push end city onto stack

	while(strcmp(currentJunction->direction, start->direction) != 0)//finding the start junction
	{
		currentJunction = currentJunction->nextJCT;
	}

	if(strcmp(start->direction, end->direction) != 0) //cities on different branches
	{
		while(currentCity->prev != NULL)
		{
			currentCity = currentCity->prev;
			Push(route, currentCity->name);
		}

<<<<<<< HEAD
		Push(route, "junction");
		currentCity = currentJunction->nextCity;
=======
	Push(route, "junction");
        current = currentJunction->nextCity;
>>>>>>> 3a8849a8d8b879db81ef2ec04cd518349be34323

		while(strcmp(currentCity->name, start->name) != 0)
		{
			Push(route, currentCity->name);
			currentCity = currentCity->next;
		}

		Push(route, currentCity->name);
	}

<<<<<<< HEAD
	else if(start->position > end->position) //same branch, start is further down than end
	{
		while(strcmp(currentCity->name, start->name) != 0)
		{
			currentCity = currentCity->next;
			Push(route, currentCity->name);
		}
	}

	else //start is further up than end
	{
		while(strcmp(currentCity->name, start->name) != 0)
		{
			currentCity = currentCity->prev;
			Push(route, currentCity->name);
		}
	}

	return;
=======
    else if(start->position > end->position) //same branch, start is further down than end
    {
        while(strcmp(current->name, start->name) != 0)
        {
            current = current->next;
            Push(route, current->name);
        }
    }

    else //start is further up than end
    {
        while(strcmp(current->name, start->name) != 0)
        {
            current = current->prev;
            Push(route, current->name);
        }
    }

    return;
>>>>>>> 3a8849a8d8b879db81ef2ec04cd518349be34323
}

/********************************************
*printCityList
* Prints our a list of available cities
*********************************************/
void printCityList(jct *root)
{
	city *currentCity;
	jct *currentJunction;
	currentJunction = root->nextJCT;
	currentCity = currentJunction->nextCity;
	char breakCity[MAX_NAME];
	strcpy(breakCity, currentCity->name); //sets break condition for loop
	int i;
	int length;
	int count = 0;
	while(1)
	{
		length = strlen(currentCity->name);
		printf("%s", currentCity->name);
		for(i = 0; i < (MAX_NAME - length); i++) printf(" "); //provides even spacing by accounting for name length
		if(count % 2 == 1) printf("\n"); //formats printing into two columns

		if(currentCity->next == NULL) //end of branch
		{
			currentJunction = currentJunction->nextJCT;
			currentCity = currentJunction->nextCity;
		}
		else //traverse branch
		{
			currentCity = currentCity->next;
		}

		if(strcmp(currentCity->name, breakCity) == 0) //traversed all possible cities
		{
			break;
		}
		count++;
	}
	printf("\n");
	return;
}

/********************************************
*input
* Get user input, and set start
* and ending city pointers
*********************************************/
void input(jct *root, city *start, city *end) //root of the map, pointer to the starting city, pointer to the ending city
{
	char startingCity[MAX_NAME], endingCity[MAX_NAME];

	while(1) //get valid starting city
	{
		printf("Enter the starting city(or 'citylist' for a list of available cities): ");
		fgets(startingCity, MAX_NAME, stdin);
		sanitizeInput(startingCity);

		if(strcmp(startingCity, "Citylist") == 0) //prints out a list of cities in the map
		{
			printCityList(root);
		}
		else if(citySearch(startingCity, start, root) == 1) //if city exists in the map sets starting city and returns
		{
			break;
		}
	}
	while(1) //get valid ending city
	{
		printf("Enter the destination city(or 'citylist' for a list of available cities): ");
		fgets(endingCity, MAX_NAME, stdin);
		sanitizeInput(endingCity);

		if(strcmp(endingCity, "Citylist") == 0)//prints out a list of cities in the map
		{
			printCityList(root);
		}
		else if(strcmp(startingCity, endingCity) == 0) //starting and ending cities cannot be the same
		{
			printf("You're already there. Try another destination.\n");
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
void swapDirection(city *currentDirection)
{
	if(strcmp(currentDirection->direction, "north") == 0) strcpy(currentDirection->direction, "south");
	else if(strcmp(currentDirection->direction, "south") == 0) strcpy(currentDirection->direction, "north");
	else if(strcmp(currentDirection->direction, "east") == 0) strcpy(currentDirection->direction, "west");
	else if(strcmp(currentDirection->direction, "west") == 0) strcpy(currentDirection->direction, "east");
}

/****************************************
*printRoute
* Pops elements from a stack and prints.
******************************************/
void printRoute(STACK *route, city *start, city *end)
{
	STACK_ELEMENT temp;
	temp = Pop(route);
	city *currentDirection;
	char highway[10];

	strcpy(currentDirection->direction, start->direction);

	if(strcmp(start->direction, "north") == 0 || strcmp(start->direction, "south") == 0) strcpy(highway, "Interstate 5");
	else if(strcmp(start->direction, "east") == 0 || strcmp(start->direction, "west") == 0) strcpy(highway, "Highway 26");

	if(strcmp(start->direction, end->direction) != 0 || start->position > end->position) //if moving towards to the junction
	{
		swapDirection(currentDirection); //correct for direction of movement
	}
	printf("\nHeading %s out of %s on %s... ", currentDirection->direction, temp.name, highway);

 	while(strcmp(temp.name, end->name) != 0)    //printing out the STACK in order
	{
		temp = Pop(route);
		if(strcmp(temp.name, "junction") != 0 && strcmp(temp.name, end->name) != 0)  //don't print junction or last element
		{
			printf("passing %s... ", temp.name);
		}
		else if(strcmp(temp.name, "junction") == 0) //moving between branches, might change onto different highway
		{
			if(strcmp(end->direction, currentDirection->direction) == 0) //if staying on the same highway
    			{
        			printf("continuing %s on %s...", currentDirection->direction, highway);
    			}
    			else //turning onto new highway
    			{
        			if(strcmp(highway, "Interstate 5") == 0) strcpy(highway, "Highway 26");
        			else strcpy(highway, "Interstate 5");
        			printf("turning %s onto %s...", end->direction, highway);
    			}
		}
	}

	printf("arrived at %s.\n\n", temp.name);
	return;
}
