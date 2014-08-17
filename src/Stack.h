#ifndef __STACK_H__
#define __STACK_H__

#include "LinkedList.h"
//Stack structure.
typedef struct
{
	void *topOfStack;

}Stack;

Stack *createStack();
void stackPush(void *data,Stack *stack);
void * stackPop(Stack *stack);
void destroyStack(Stack *stack);

#endif //__STACK_H__