#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
*standardizeInput
* modifies a string into a standard format
\**********************************************/
void standardizeInput(char input[])
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
