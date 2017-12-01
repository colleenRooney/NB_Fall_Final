#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#define FILES_TO_READ 4
#define MAX_LENGTH 20
#define COST_PER_MILE 0.09 //cost per mile at 30mi/gal and $2.55/gal
#define RED "\x1b[1;31m"
#define COLOR_RESET "\x1b[0m"


typedef struct city { //stores city info
    char name[MAX_LENGTH];
	char direction[MAX_LENGTH];
	float miles;
    struct city *next;
    struct city *prev;
    } city;

typedef struct junction { //stores junction info
    char name[MAX_LENGTH];
    city *nextCity;
	char direction[MAX_LENGTH];
    struct junction *nextJunction;
    } junction;

#endif
