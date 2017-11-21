typedef struct STACK_ELEMENT {
	char name[40];
	struct STACK_ELEMENT *prev;
} STACK_ELEMENT;

typedef struct STACK {
	STACK_ELEMENT *head;
} STACK;

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
struct STACK_ELEMENT Pop(STACK *s)
{
	STACK_ELEMENT *temp;
	temp = s->head;
	s->head = s->head->prev;
	return *temp;
}

/***********************************************
*peek
* returns top  item without destruction
************************************************/
struct STACK_ELEMENT Peek(STACK *s)
{
	return *(s->head);
}

