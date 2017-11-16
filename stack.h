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
void createStack(STACK *r)
{
	STACK_ELEMENT *head = malloc(sizeof(STACK_ELEMENT));
	head->prev = NULL;
	strcpy(head->name, "END OF THE LINE");
	r->head = head;
	return;
}
/********************************************
*push
* pushs an item onto the STACK stack
*********************************************/
void Push(STACK *r, char cityName[])
{
	STACK_ELEMENT *temp;
	temp = r->head;
	r->head = malloc(sizeof(STACK_ELEMENT));
	strcpy(r->head->name, cityName);
	r->head->prev = temp;
	return;
}

/************************************
*pop
* returns last item off the stack
*************************************/
struct STACK_ELEMENT Pop(STACK *r)
{
	STACK_ELEMENT *temp;
	temp = r->head;
	r->head = r->head->prev;
	return *temp;
}

/***********************************************
*peek
* returns top  item without destruction
************************************************/
struct STACK_ELEMENT Peek(STACK *r)
{
	return *(r->head);
}

