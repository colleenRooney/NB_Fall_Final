#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNAME 20

/************************************************/
/* function: pathSearch			                  	*/
/* description				                        	*/
/* ...						                              */
/************************************************/
void pathSearch(jct *branch, city *start, city *destination, cStack *stack)
{
   int state = 1;
  	cPush(stack, start);
  	while(strcmp(start->name, destination->name) != 0)
  	{
	    	if((count_cStack(*stack) == 0)) state = 3;
		   else if(start->next == NULL) state = 2;
	  	 else if(start->prev == NULL) state = 4;

		  switch(state){
	  	case 1: 			//not at end of branch, searching down branch
		  	 cPush(stack, start);
			   start = start->next;
		  	 break;
	  	case 2:				//at end of stack, reverse direction
	  		 cPop(stack);
		  	 start = start->prev;
			break;
		  case 3: 			//reached starting city
			   if((count_cStack(stack) == 0) cPush(stack, start->next);
			   cPush(stack, start);
			   start = start->prev;
			   break;
		  case 4:				//at junction
			
			   branch = branch->jctnext;
			   start = branch->citynext;
		   	 state = 1;
			   break;
		  }
   cPush(stack, start);
   }
	print_cStack(*stack);	
}
