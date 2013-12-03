#include <stdio.h>
#include <stdlib.h>

#include "sqqueue.h"

/*
 * 队列的顺序存储结构
 * 循环队列
 */
struct t_sqqueue {
	QueueElemType *base; /* */
	int front; /* 头指针, 若队列不空, 指向队列头元素 */
	int rear; /* 尾指针, 若队列不空, 指向队列尾元素的下一个位置(空位置) */
};

/* */
struct t_sqqueue *queue_init(void)
{
	struct t_sqqueue *pQueue;

	if((pQueue = malloc(sizeof(struct t_sqqueue))) == NULL)
	{
		printf("queue malloc err 1\n");
		return NULL;
	}
	printf("pQueue = %p\n", pQueue);
	if((pQueue->base = malloc(sizeof(QueueElemType) * QUEUE_MAX_SIZE)) == NULL)
	{
		printf("queue malloc err 2\n");
		return NULL;
	}
	printf("pQueue->base = %p\n", pQueue->base);
	pQueue->front = 0;
	pQueue->rear = 0;

	return pQueue;
}

void queue_destroy(struct t_sqqueue *pQueue)
{
	free(pQueue->base);
	free(pQueue);
}

void queue_clear(struct t_sqqueue *pQueue)
{
	pQueue->front = 0;
	pQueue->rear = 0;
}

Status queue_empty(struct t_sqqueue *pQueue)
{
	return (pQueue->front == pQueue->rear);
}

Status queue_full(struct t_sqqueue *pQueue)
{
	return ((pQueue->rear + 1) % QUEUE_MAX_SIZE == pQueue->front);
}

int queue_length(struct t_sqqueue *pQueue)
{
	return (pQueue->rear - pQueue->front + QUEUE_MAX_SIZE) % QUEUE_MAX_SIZE;
}

int queue_free_len(struct t_sqqueue *pQueue)
{
	return (QUEUE_MAX_SIZE - queue_length(pQueue) - 1);
}

Status queue_get_head(struct t_sqqueue *pQueue, QueueElemType *e)
{
	if(queue_empty(pQueue))
		return -1;
	*e = pQueue->base[pQueue->front];

	return 0;
}

Status queue_in(struct t_sqqueue *pQueue, QueueElemType e)
{
	if(queue_empty(pQueue))
		return -1;
	pQueue->base[pQueue->rear] = e;
	pQueue->rear = (pQueue->rear + 1) % QUEUE_MAX_SIZE;

	return 0;
}

Status queue_out(struct t_sqqueue *pQueue, QueueElemType *e)
{
	if(queue_empty(pQueue))
		return -1;
	*e = pQueue->base[pQueue->front];
	pQueue->front = (pQueue->front + 1) % QUEUE_MAX_SIZE;

	return 0;
}

/* */
