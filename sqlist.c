#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

/* count starts at 1 */
#define LIST_INIT_SIZE     100
#define LIST_INCREMENT     10

#if 0
typedef struct t_sqlist {
	ListElemType *elem;
	int len;
	int size;
}SqList;
#endif
struct t_sqlist {
	ListElemType *elem;
	int len;
	int size;
};

struct t_sqlist *list_init(void)
{
	struct t_sqlist *plist;
	if((plist = malloc(sizeof(struct t_sqlist))) == NULL)
	{
		printf("malloc 1 err\n");
		return NULL;
	}
	printf("plist = %p\n", plist);

	if((plist->elem = malloc(LIST_INIT_SIZE * sizeof(ListElemType))) == NULL)
	{
		free(plist);
		printf("malloc 2 err\n");
		return NULL;
	}
	printf("plist->elem = %p\n", plist->elem);

	plist->len = 0;
	plist->size = LIST_INCREMENT;
	return plist;
}

void list_destroy(struct t_sqlist **plist)
{
	printf("*plist->elem = %p\n", (*plist)->elem);
	printf("*plist = %p\n", *plist);
	free((*plist)->elem);
	free(*plist);
	(*plist) = NULL;
}

void list_clear(struct t_sqlist *plist)
{
	plist->len = 0;
}

Status list_empty(struct t_sqlist *plist)
{
	return plist->len == 0 ? 1 : 0;
}

int list_lenght(struct t_sqlist *plist)
{
	return plist->len;
}

Status list_get_elem(struct t_sqlist *plist, int i, ListElemType *e)
{
	if(plist == NULL)
		return -1;
	if(i < 1 || i > plist->len)
		return -1;

	*e = *(plist->elem + i - 1);

	return LIST_SCUESS;
}

Status list_locate_elem(struct t_sqlist *plist, ListElemType e, Status (*compare)(ListElemType, ListElemType))
{
	int i = 1;
	ListElemType *p = plist->elem;

	while(i <= plist->len && !compare(*p++, e))
		i++;

	return (i <= plist->len ? i : 0);
}

Status list_get_prior(struct t_sqlist *plist, ListElemType cur, ListElemType *pre)
{
	int i = 2;
	ListElemType *p = plist->elem + 1;

	while(i <= plist->len && *p != cur)
	{
		p++;
		i++;
	}
	
	if(i > plist->len)
		return -1;
	
	*pre = *--p;

	return 0;
}

Status list_get_next(struct t_sqlist *plist, ListElemType cur, ListElemType *next)
{
	int i = 1;
	ListElemType *p = plist->elem;

	while(i < plist->len && *p != cur)
	{
		i++;
		p++;
	}

	if(i == plist->len)
		return -1;

	*next = *++p;
	return 0;
}

Status list_insert(struct t_sqlist *plist, int i, ListElemType e)
{
	ListElemType *newbase, *p, *q;

	if(i < 1 || i > plist->len + 1)
		return -1;

	if(plist->len >= plist->size)
	{
		if((newbase = realloc(plist->elem, (plist->size + LIST_INCREMENT) * sizeof(ListElemType))) == NULL)
			return -1;
		plist->elem = newbase;
		plist->size += LIST_INCREMENT;
	}

	q = plist->elem + i - 1; /* insert position */
	for(p = plist->elem + plist->len - 1; p >= q; p--)
		*(p+1) = *p;
	*q = e;
	plist->len++;

	return 0;
}

Status list_delect(struct t_sqlist *plist, int i, ListElemType *e)
{
	ListElemType *p, *q;

	if(i < 1 || i > plist->len)
		return -1;

	p = plist->elem + i - 1; /* delect position */
	if(e != NULL)
		*e = *p;
	q = plist->elem + plist->len - 1;
	for(++p; p <= q; p++)
		*(p-1) = *p;
	
	plist->len--;
	return 0;
}

void list_traverse(struct t_sqlist *plist, void (*vi)(ListElemType *))
{
	int i;
	ListElemType *p = plist->elem;
	for(i = 1; i <= plist->len; i++)
		vi(p++);
}

/* eof sqlist.c */
