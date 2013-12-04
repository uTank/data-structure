#include <stdio.h>
#include <stdlib.h>

#include "sqqueue.h"

/*
 * 队列的顺序存储结构
 * 循环队列
 */
struct t_sqqueue {
	QueueElemType *base; /* */
	int head; /* 头指针, 若队列不空, 指向队列头元素 */
	int tail; /* 尾指针, 若队列不空, 指向队列尾元素的下一个位置(空位置) */
	int size;
};

/* */
struct t_sqqueue *queue_init(int size)
{
	struct t_sqqueue *pQueue;

	if((pQueue = malloc(sizeof(struct t_sqqueue))) == NULL)
	{
		printf("queue malloc err 1\n");
		return NULL;
	}
	pQueue->size = size;
//	printf("pQueue = %p\n", pQueue);
	if((pQueue->base = malloc(sizeof(QueueElemType) * pQueue->size)) == NULL)
	{
		printf("queue malloc err 2\n");
		free(pQueue);
		return NULL;
	}
//	printf("pQueue->base = %p\n", pQueue->base);
	pQueue->head = 0;
	pQueue->tail = 0;

	return pQueue;
}

void queue_destroy(struct t_sqqueue *pQueue)
{
//	printf("*pQueue = %p\n", *pQueue);
//	printf("(*pQueue)->base = %p\n", (*pQueue)->base);
	free(pQueue->base);
	free(pQueue);
//	*pQueue = NULL;
}

void queue_clear(struct t_sqqueue *pQueue)
{
	pQueue->head = 0;
	pQueue->tail = 0;
}

Status queue_empty(struct t_sqqueue *pQueue)
{
	return (pQueue->head == pQueue->tail);
}

Status queue_full(struct t_sqqueue *pQueue)
{
	return ((pQueue->tail + 1) % pQueue->size == pQueue->head);
}

int queue_length(struct t_sqqueue *pQueue)
{
	return (pQueue->tail - pQueue->head + pQueue->size) % pQueue->size;
}

int queue_free_len(struct t_sqqueue *pQueue)
{
	return (pQueue->size - queue_length(pQueue) - 1);
}

Status queue_get_head(struct t_sqqueue *pQueue, QueueElemType *e)
{
	if(queue_empty(pQueue))
		return -1;

	*e = pQueue->base[pQueue->head];

	return 0;
}

Status queue_in(struct t_sqqueue *pQueue, QueueElemType e)
{
	if(queue_empty(pQueue))
		return -1;

	pQueue->base[pQueue->tail] = e;
	pQueue->tail = (pQueue->tail + 1) % pQueue->size;

	return 0;
}

Status queue_out(struct t_sqqueue *pQueue, QueueElemType *e)
{
	if(queue_empty(pQueue))
		return -1;

	*e = pQueue->base[pQueue->head];
	pQueue->head = (pQueue->head + 1) % pQueue->size;

	return 0;
}

int queue_in_s(struct t_sqqueue *pQueue, QueueElemType *buf, int size)
{
	int i, len;

	len = queue_free_len(pQueue);
	if(len > size)
		len = size;
	for(i = 0; i < len; i++)
	{
		pQueue->base[pQueue->tail] = buf[i];
		pQueue->tail = (pQueue->tail + 1) % pQueue->size;
	}
	return 0;
}

int queue_out_s(struct t_sqqueue *pQueue, QueueElemType *buf, int size)
{
	int i, len;

	len = queue_length(pQueue);
	if(len > size)
		len = size;
	for(i = 0; i < len; i++)
	{
		buf[i] = pQueue->base[pQueue->head];
		pQueue->head = (pQueue->head + 1) % pQueue->size;
	}
	return len;
}

int queue_peep(struct t_sqqueue *pQueue, QueueElemType *buf, int size)
{
	int i, tail, len;

	len = queue_length(pQueue);
	if(len >= size)
		len = size;
	tail = pQueue->tail;
	for(i = 0; i < len; i++)
	{
		buf[i] = pQueue->base[tail];
		tail = (tail + 1) % pQueue->size;
	}
	return len;
}


/* */
