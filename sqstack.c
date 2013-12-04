#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

struct t_sqstack {
	StackElemType *data;
	int top;
	int size;
};

struct t_sqstack *stack_init(int size)
{
	struct t_sqstack *pStack;

	if((pStack = malloc(sizeof(struct t_sqstack))) == NULL)
	{
		printf("stack malloc err 1\n");
		return NULL;
	}
//	printf("pStack = %p\n", pStack);
	pStack->size = size;
	if((pStack->data = malloc(sizeof(StackElemType) * pStack->size)) == NULL)
	{
		free(pStack);
		printf("stack malloc err 2\n");
		return NULL;
	}
//	printf("pStack->data = %p\n", pStack->data);
	pStack->top = -1;

	return pStack;
}

Status stack_push(struct t_sqstack *pStack, StackElemType e)
{
	if(pStack->top == pStack->size - 1)
		return -1;

	pStack->top++;
	pStack->data[pStack->top] = e;
	return 0;
}

Status stack_pop(struct t_sqstack *pStack, StackElemType *e)
{
	if(pStack->top == -1)
		return -1;

	if(e != NULL)
		*e = pStack->data[pStack->top];
	pStack->top--;

	return 0;
}

Status stack_get_top(struct t_sqstack *pStack, StackElemType *e)
{
	if(pStack->top == -1)
		return -1;

	if(e != NULL)
		*e = pStack->data[pStack->top];

	return 0;
}

Status stack_empty(struct t_sqstack *pStack)
{
	return (pStack->top == -1);
}

void stack_clear(struct t_sqstack *pStack)
{
	pStack->top = -1;
}

int stack_lenght(struct t_sqstack *pStack)
{
	return (pStack->top + 1);
}

void stack_destroy(struct t_sqstack *pStack)
{
//	printf("(*pStack)->data = %p\n", (*pStack)->data);
//	printf("*pStack = %p\n", *pStack);
	free(pStack->data);
	free(pStack);
//	*pStack = NULL;
}

void stack_traverse(struct t_sqstack *pStack, void (*vi)(StackElemType))
{
	int i = 0;

	while(i <= pStack->top)
	{
		vi(pStack->data[i++]);
	}
}
/* */
