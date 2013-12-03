#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

struct t_sqstack {
	StackElemType *data;
	int top;
};

struct t_sqstack *stack_init(void)
{
	struct t_sqstack *pStack;

	if((pStack = malloc(sizeof(struct t_sqstack))) == NULL)
	{
		printf("stack malloc err 1\n");
		return NULL;
	}
	printf("pStack = %p\n", pStack);
	if((pStack->data = malloc(sizeof(StackElemType) * SQ_STACK_MAX_SIZE)) == NULL)
	{
		free(pStack);
		printf("stack malloc err 2\n");
		return NULL;
	}
	printf("pStack->data = %p\n", pStack->data);
	pStack->top = -1;

	return pStack;
}

Status stack_push(struct t_sqstack *pStack, StackElemType e)
{
	if(pStack->top == SQ_STACK_MAX_SIZE - 1)
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
	free(pStack->data);
	free(pStack);
}

void stack_traverse(struct t_sqstack *pStack, void (*vi)(StackElemType))
{
	int i = 0;

	while(i <= pStack->top)
	{
		vi(pStack->data[i++]);
	}
}

// TODO: 1
void conversion(unsigned int n)
{
#define CONVER_TO		(8)
	struct t_sqstack *pStack;
	StackElemType e;

	pStack = stack_init();
	while(n)
	{
		stack_push(pStack, n % CONVER_TO);
		n /= CONVER_TO;
	}
	while(!stack_empty(pStack))
	{
		stack_pop(pStack, &e);
		if(e <= 9)
			printf("%d", e);
		else
			printf("%c", e - 10 + 'a');
	}
	printf("\r\n");
	stack_destroy(pStack);
}

// TODO:2
int check(const char *pt)
{
	struct t_sqstack *pStack;
	StackElemType e;

	pStack = stack_init();
	while(*pt)
	{
		switch(*pt)
		{
		case '(':
		case '[':
		case '{':
			stack_push(pStack, *pt++);
			break;
		case ')':
		case ']':
		case '}':
			if(stack_empty(pStack))
			{
				stack_destroy(pStack);
				return -2;
			}
			stack_pop(pStack, &e);
			if((*pt == ')' && e != '(') || (*pt == ']' && e != '[') || (*pt == '}' && e != '{'))
			{
				stack_destroy(pStack);
				return -3;
			}
			pt++;
			break;
		default:
			pt++;
			break;
		}
	}
	if(!stack_empty(pStack))
	{
		stack_destroy(pStack);
		return -1;
	}

	stack_destroy(pStack);
	printf("success!\n");
	return 0;
}

// TODO:3
