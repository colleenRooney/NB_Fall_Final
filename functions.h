#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "definitions.h"
#include "stack.h"

//function prototypes
void createMap(junction *root);
int citySearch(char name[], city *c, junction *root);
void makePath(junction *root, city *start, city *end, STACK *route, float *milesTotal);
void printCityList(junction *root);
void userInput(junction *root, city *start, city *end);
void swapDirection(city *currentDirection);
void printRoute(STACK *route, city *start, city *end, float *milesTotal);

#endif
