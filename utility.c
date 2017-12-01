#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

/*********************************************\
*isaLetter
* returns true if character is a letter
\**********************************************/
int isaLetter(char letter) //if character is a letter return 1, else return 0
{
	if(((letter <= 122) && (letter >= 97)) || ((letter <= 90) && (letter >= 65))) return 1;
	else return 0;
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
	if((*letter <= 90) && (*letter >= 65)) *letter = *letter + 32;
	return;
}
 
/*********************************************\
*capitalize
* capitalizes input if input is lowercase
\**********************************************/
void capitalize(char *letter) //function returns uppercase equivalent of lowercase letter
{
	if((*letter <= 122) && (*letter >= 97)) *letter = *letter - 32;
	return;
}

/*********************************************\
*standardizeInput
* modifies a string into a standard format
\**********************************************/
void standardizeInput(char input[])
{
	int length = strlen(input);

	for(int i = 0; i < length; i++)
	{
		if(input[i] == '\n') input[i] = '\0'; //terminate string
		else if(i == 0 || isaSpace(input[i-1])) capitalize(&input[i]); //if first letter or new wor

		else if(isaSpace(input[i]) && !isaLetter(input[i+1])) input[i]='\0'; //if character is a space without a following letter
		else decap(&input[i]);
	}
}
/*************************************************************
* breakupInput
* Format of the map files is <city name>|<miles>
* Breaks up input string so the input only contains the name
* Moves the float after the | seperator to a new array then
* converts to a float and loads into cityMiles
**************************************************************/
void breakupInput(char input[], float *cityMiles)
{
	char miles[MAX_LENGTH]; //holds values to be converted to float
	int i = 0, j = 0;
	char *end = NULL; //necessary for strtof function, doesn't actually do anything

	while(input[i] != '|') //finding the seperator
	{
		i++;
		if(input[i] == '\n') //if it finds the end of the string without a serperator
		{
			input[i] = '\0';
			return;
		}
	}

	input[i] = '\0'; //replacing seperator with string terminator
	i++;

	while(input[i] != '\n') //loading from input string to number array
	{
		miles[j] = input[i];
		input[i] = '\0';
		i++;
		j++;
	}

	miles[j] = '\0';
	*cityMiles = strtof(miles, &end); //converts miles array to float
	return;
}
