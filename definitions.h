#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#define FILES_TO_READ 4
#define MAX_NAME 20

typedef struct city { //stores city info
    char name[20];
	char direction[20];
	int position;
    struct city *next;
    struct city *prev;
    } city;

typedef struct junction { //stores junction info
    char name[10];
    city *nextCity;
	char direction[10];
    struct junction *nextJunction;
    } junction;

#endif
