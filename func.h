#define FILES_TO_READ 2
#define MAX_NAME 20

/*********************************************\
* sanitizeInput
* modifies a string into a uniform structure
\**********************************************/
void sanitizeInput(char input[])
{
	int length = strlen(input);
	for(int i=0;i<length;i++)
	{
		if(input[i] == '\n')
		{
			input[i] = '\0';
		}
		else if(i==0 || input[i-1] == 32)
		{
			if(input[i] >= 97 && input[i] <= 122) input[i] = input[i]-32; //Capitalize lowercase letter at start or if a new word
		}
		else if(input[i] == 32 && input[i+1] < 65 || input[i] > 122 || (input[i] > 90 && input[i] < 97)) 
		{
			input[i] = '\0'; //letter is a space and another letter does not follow, change to string terminator
		}
		else
		{
			if(input[i] >= 65 && input[i] <= 90) input[i] = input[i] + 32; //decapatilzes uppercase letters that shoudld be lower case
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
	city *n, *lastcity;
	jct *last,*curr, *firstjct;
	int count = 0;
	int j = 0;

	FILE *fp;

	for(int i=0;i<FILES_TO_READ;i++)
	{
		//opening proper file
		if(i==0) fp = fopen("north", "r");
		else if(i==1) fp = fopen("south", "r"); 
		else if(i==2) fp = fopen("east", "r"); 
		else if(i==3) fp = fopen("west", "r");

		//create junction node
		curr = malloc(sizeof(jct));
		curr->nextJCT = NULL;
		curr->nextCity = NULL;
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
		removeEnd(cityName);
		while(strcmp(cityName, "*") != 0) // The * denotes end of file
		{
			n = malloc(sizeof(city));
			n->next = NULL;
			n->prev = NULL;
			strcpy(n->name, cityName);
			if(j == 0)//connecting first city to the junction
			{
				curr->nextCity = n;
				j++;
			}
			else//for rest of cities in list
			{
				lastcity->next = n;
				n->prev = lastcity;
			}
			lastcity = n;
			fgets(cityName, MAX_NAME, fp);
			removeEnd(cityName);
		}
		j=0;
		fclose(fp);
	}
	last->nextJCT = firstjct;
}

/*************************************************************************
*citySearch
* Takes in a city, finds it in the map, and points a pointer to it
* returns 1 if the city is in the map, 0 if it is not
**************************************************************************/
int citySearch(char name[], city *r, jct *root)
{
	//variables
	static int check = 0; //indicator to ensure root is only moved on first search
	char initialCity[MAX_NAME]; // starting city
	city *search; //city to be searched
	jct *j; //current junction node
	//setting break condiiton
	j = root->nextJCT;
	search = j->nextCity;
	strcpy(initialCity, search->name);

	while(1)
	{
		if(strcmp(name, search->name) == 0) //checks for break condition
		{
			strcpy(r->name, search->name); //sets incoming pointer to the current city node
			r->next = search->next;
			r->prev = search->prev;
			if( check == 0)
			{
				root->nextJCT = j;
				check++;
			}
			return 1;
		}

		if(search->next == NULL) //if at the end of a branch go to next junction branch
		{
			j = j->nextJCT;
			search = j->nextCity;
			if(strcmp(search->name, initialCity) == 0) //checks to see if at original branch, if so exits
			{
				printf("City does not exist in map.\n");
				return 0;
			}
		}
		else search = search->next; //traverses the list
	}
}

/**********************************************************************
*pathSearch
* finds a route from the starting city to an ending city
* returns an int for how many steps between the start and end for
* use in the path array
***********************************************************************/
void pathSearch(jct *root, city *s, city *end, STACK *c)
{
	STACK o;
	createStack(&o);
	int i = 0;int z = 0;
	int count = 0;
	city *search;
	jct *j;
	j = root->nextJCT;
	STACK_ELEMENT temp;
	search = s;
	Push(&o, s->name);
	while(1)
	{
		if(strcmp(search->name, end->name) == 0) //found the end city
		{
			c->head = o.head;
			return;
		}
		else if(search->next == NULL) //end of the branch
		{
			switch(z){
			case 0: //for the first search that involves the branch with the starting city
				while(1) //Popping cities off stack until we reach the start
				{
					temp = Peek(&o);
					if(strcmp(s->name, temp.name) != 0)
					{
						temp = Pop(&o);
					}
					else break;
				}
				search = s; //go back to start
				while(search->prev != NULL)
				{
					search = search->prev;
					Push(&o, search->name);
					if(strcmp(search->name, end->name) == 0) //found the end city
					{
						c->head = o.head;
						return;
					}
				}

				Push(&o, "i5/Hwy_26 junction");
				j = j->nextJCT;
				search = j->nextCity;
				Push(&o, search->name);
				z = 1;
				break;

			case 1: //for reversing up a branch
				while(search->prev != NULL)
				{
				    temp = Pop(&o);
				    search = search->prev;
				}
				Pop(&o);
				j = j->nextJCT;
				search = j->nextCity;
				Push(&o, search->name);
				break;
			}
		}

		else //moving from city to city
		{
			search = search->next;
			Push(&o, search->name);
		}
	}
}

/********************************************
*printCityList
* Prints our a list of available cities
*********************************************/
void printCityList(jct *cityListRoot)
{
	city *current;
	jct *j;
	j = cityListRoot->nextJCT;
	current = j->nextCity;
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
			j = j->nextJCT;
			current = j->nextCity;
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
			strcpy(start->name, startingCity);
			break;
		}
	}
	while(1) //get valid ending city
	{
		printf("Enter the destination city: ");
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
			strcpy(end->name, endingCity);
			break;
		}
	}
}

void printRoute(STACK orig, city *start, city *end)
{
	STACK reverse;
	createStack(&reverse);
	STACK_ELEMENT temp;
	temp = Peek(&orig);
	int i =0;
	while(strcmp(temp.name, start->name) != 0)  //Popping items from original stack to reversed stack
	{
		i++;
		temp = Pop(&orig);
    		Push(&reverse, temp.name);
   	}
	temp = Pop(&reverse);

	printf("\nYour route is: ");
 	while(strcmp(temp.name, end->name) != 0)    //printing out the STACK in order
	{
		printf("%s to ", temp.name);
		temp = Pop(&reverse);
		//if(strcmp(temp.name, "North Portland") == 0 || strcmp(temp.name, "South Portland") == 0))
	}

	printf("%s.\n\n", temp.name);
	return;
}
