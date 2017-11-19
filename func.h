
#define FILES_TO_READ 2
#define MAX_NAME 20

/*********************************************\
* sanitizeInput
* modifies a string into a standard format
\**********************************************/
void sanitizeInput(char input[])
{
	int length=strlen(input);
	for(int i=0;i<length;i++)
	{
		if(input[i]=='\n')
		{
			input[i]='\0';
		}
		else if(i==0 || input[i-1]==32)
		{
			if(input[i]>=97 && input[i]<=122) input[i]=input[i]-32; //Capitalize lowercase letter at start or if a new word
		}
		else if(input[i]==32 && input[i+1]<65 || input[i]>122 || (input[i]>90 && input[i]<97))
		{
			input[i]='\0'; //letter is a space and another letter does not follow, change to string terminator
		}
		else
		{
			if(input[i]>=65 && input[i]<=90) input[i]=input[i]+32; //decapatilzes uppercase letters that shoudld be lower case
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
	jct *last,*curr, *firstjct;
	int positionIndicator = 0;
	int firstCity = 0;

	FILE *fp;

	for(int i=0;i<FILES_TO_READ;i++)
	{
		//opening proper file
		if(i==0) fp = fopen("north", "r");
		else if(i==1) fp = fopen("south", "r");
		else if(i==2) fp = fopen("east", "r");
		else if(i==3) fp = fopen("west", "r");

		//create junction node
		fgets(directionIndicator, 10, fp);
		sanitizeInput(directionIndicator);
		directionIndicator[0] = directionIndicator[0]+32;
		curr = malloc(sizeof(jct));
		curr->nextJCT = NULL;
		curr->nextCity = NULL;
		strcpy(curr->direction, directionIndicator);

		if(i==0) //points root to first junction
		{
			root->nextJCT = curr;
			firstjct = curr;
		}
		else //set last junction to current junction
		{
			last->nextJCT = curr;
		}
		last = curr; //changes junction to last junction

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
				curr->nextCity = newCity;
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
	last->nextJCT = firstjct;
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
	//setting break condiiton
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
* makePath
* determines state from direction and
* position values of start and end and
* loads a stack with the path
******************************************/
void makePath(jct *root, city *start, city *end, STACK *route)
{
    jct *currentJunction = root->nextJCT;
    city *current;
    current = end;
    Push(route, current->name); //push end city onto stack

    while(strcmp(currentJunction->direction, start->direction) != 0)//finding the start junction
    {
        currentJunction = currentJunction->nextJCT;
    }

    if(strcmp(start->direction, end->direction) != 0) //cities on different branches
    {
        while(current->prev != NULL)
        {
            current = current->prev;
            Push(route, current->name);
        }

        current = currentJunction->nextCity;

        while(strcmp(current->name, start->name) != 0)
        {
            Push(route, current->name);
            current = current->next;
        }

        Push(route, current->name);
    }

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
}
/********************************************
*printCityList
* Prints our a list of available cities
*********************************************/
void printCityList(jct *cityListRoot)
{
	city *current;
	jct *currentJunction;
	currentJunction = cityListRoot->nextJCT;
	current = currentJunction->nextCity;
	char breakCity[MAX_NAME];
	strcpy(breakCity, current->name);
	int i;
	int length;
	int count = 0;
	while(1)
	{
		length = strlen(current->name);
		printf("%s", current->name);
		for(i=0; i<(MAX_NAME-length); i++) {printf(" ");}
		count++;
		if(count == 2){printf("\n"); count = 0;}

		if(current->next == NULL)
		{
			currentJunction = currentJunction->nextJCT;
			current = currentJunction->nextCity;
		}
		else
		{
			current = current->next;
		}

		if(strcmp(current->name, breakCity) == 0)
		{
			break;
		}
	}
	printf("\n");
}

/********************************************
*input
* Get user input, and set start
* and ending city pointers
*********************************************/
void input(jct *root, city *start, city *end, jct *cityListRoot) //root of the map, pointer to the starting city, pointer to the ending city
{
	char startingCity[MAX_NAME], endingCity[MAX_NAME];

	while(1) //get valid starting city
	{
		printf("Enter the starting city(or 'citylist' for a list of available cities): ");
		fgets(startingCity, MAX_NAME, stdin);
		sanitizeInput(startingCity);

		if(strcmp(startingCity, "Citylist") == 0) //prints out a list of cities in the map
		{
			printCityList(cityListRoot);
		}
		else if(citySearch(startingCity, start, root) == 1) //checks if city exists in the map, if true then sets starting city and returns
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
			printCityList(cityListRoot);
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
void swapDirection(city *currentDirection)
{
	if(strcmp(currentDirection->direction, "north") == 0) strcpy(currentDirection->direction, "south");
	else if(strcmp(currentDirection->direction, "south") == 0) strcpy(currentDirection->direction, "north");
	else if(strcmp(currentDirection->direction, "east") == 0) strcpy(currentDirection->direction, "west");
	else if(strcmp(currentDirection->direction, "west") == 0) strcpy(currentDirection->direction, "east");
}
/****************************************
* printRoute
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

	if(strcmp(start->direction, end->direction) != 0 || start->position > end->position) // if we are moving closer to the junction, reverse the direction of the branch
	{
		swapDirection(currentDirection);
	}
	printf("\nHeading %s out of %s on %s... ", currentDirection->direction, temp.name, highway);

 	while(strcmp(temp.name, end->name) != 0)    //printing out the STACK in order
	{
		printf("passing %s... ", temp.name);
		temp = Pop(route);
	}

	printf("arrived at %s.\n\n", temp.name);
	return;
}
