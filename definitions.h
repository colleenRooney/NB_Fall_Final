#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#define FILES_TO_READ 4
#define MAX_LENGTH 20

typedef struct city { //stores city info
    char name[MAX_LENGTH];
	char direction[MAX_LENGTH];
	int position;
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
