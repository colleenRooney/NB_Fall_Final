typedef struct city { //stores city info
    char name[40];
    struct city *next;
    struct city *prev;
    } city;

typedef struct jct { //stores junction info
    char name[10];
    city *nextCity;
    struct jct *nextJCT;
    } jct;
