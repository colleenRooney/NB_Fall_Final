#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "definitions.h"

/******************************
*createStack
* creates a new stack
******************************/
void createStack(STACK *s)
{
	STACK_ELEMENT *head = malloc(sizeof(STACK_ELEMENT));
	head->prev = NULL;
	strcpy(head->name, "END OF THE LINE");
	s->head = head;
	return;
}
/********************************************
*push
* pushs an item onto the STACK stack
*********************************************/
void Push(STACK *s, char cityName[])
{
	STACK_ELEMENT *temp;
	temp = s->head;
	s->head = malloc(sizeof(STACK_ELEMENT));
	strcpy(s->head->name, cityName);
	s->head->prev = temp;
	return;
}

/************************************
*pop
* returns last item off the stack
*************************************/
city Pop(STACK *s)
{
	STACK_ELEMENT *temp;
	city p;
	temp = s->head;
	strcpy(p.name, temp->name);
	s->head = s->head->prev;
	free(temp);
	return p;
}

/***********************************************
*peek
* returns top  item without destruction
************************************************/
city Peek(STACK *s)
{
	city p;
	strcpy(p.name, s->head->name);
	return p;
}
