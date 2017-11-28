#ifndef _STACK_H
#define _STACK_H

typedef struct STACK_ELEMENT {
    char name[40];
    struct STACK_ELEMENT *prev;
} STACK_ELEMENT;

typedef struct STACK {
    STACK_ELEMENT *head;
} STACK;

void createStack(STACK *s);
void Push(STACK *s, char cityName[]);
struct city Pop(STACK *s);
struct city Peek(STACK *s);

#endif
