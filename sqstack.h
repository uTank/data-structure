#ifndef __SqStack_H_
#define __SqStack_H_

#include "base.h"

typedef int StackElemType;

//#define SQ_STACK_MAX_SIZE     (200)

struct t_sqstack;

struct t_sqstack *stack_init(int size);
Status stack_push(struct t_sqstack *pStack, StackElemType e);
Status stack_pop(struct t_sqstack *pStack, StackElemType *e);
Status stack_get_top(struct t_sqstack *pStack, StackElemType *e);
Status stack_empty(struct t_sqstack *pStack);
void stack_clear(struct t_sqstack *pStack);
int stack_lenght(struct t_sqstack *pStack);
void stack_destroy(struct t_sqstack *pStack);
void stack_traverse(struct t_sqstack *pStack, void (*vi)(StackElemType));

#endif /* __SqStack_H_ */
