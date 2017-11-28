#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#define FILES_TO_READ 4
#define MAX_LENGTH 20
#define COST_PER_MILE 0.09 //cost per mile at 30mi/gal and $2.55/gal

typedef struct city { //stores city info
    char name[MAX_LENGTH];
	char direction[MAX_LENGTH];
	int position;
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
