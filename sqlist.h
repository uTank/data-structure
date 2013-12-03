#ifndef __SqList_H_
#define __SqList_H_

typedef int  ListElemType;

#define LIST_SCUESS        (0)
#define LIST_FAILED        (-1)

#if 0
typedef struct
{
	ListElemType *elem;
	int len;
	int size;
}SqList;
#endif

struct t_sqlist;

struct t_sqlist *list_init(void);
void list_destroy(struct t_sqlist **plist);
void list_clear(struct t_sqlist *plist);
Status list_empty(struct t_sqlist *plist);
int list_lenght(struct t_sqlist *plist);
Status list_get_elem(struct t_sqlist *plist, int i, ListElemType *e);
Status list_locate_elem(struct t_sqlist *plist, ListElemType e, Status (*compare)(ListElemType, ListElemType));
Status list_get_prior(struct t_sqlist *plist, ListElemType cur, ListElemType *pre);
Status list_get_next(struct t_sqlist *plist, ListElemType cur, ListElemType *next);
Status list_insert(struct t_sqlist *plist, int i, ListElemType e);
Status list_delect(struct t_sqlist *plist, int i, ListElemType *e);
void list_traverse(struct t_sqlist *plist, void (*vi)(ListElemType *));

#endif
