#ifndef __SqQueue_H_
#define __SqQueue_H_

#include "base.h"

typedef int QueueElemType;

//#define QUEUE_MAX_SIZE     (1024+1)

struct t_sqqueue;

struct t_sqqueue *queue_init(int size);
void queue_destroy(struct t_sqqueue *pQueue);
void queue_clear(struct t_sqqueue *pQueue);
Status queue_empty(struct t_sqqueue *pQueue);
Status queue_full(struct t_sqqueue *pQueue);
int queue_length(struct t_sqqueue *pQueue);
int queue_free_len(struct t_sqqueue *pQueue);
Status queue_get_head(struct t_sqqueue *pQueue, QueueElemType *e);
Status queue_in(struct t_sqqueue *pQueue, QueueElemType e);
Status queue_out(struct t_sqqueue *pQueue, QueueElemType *e);
int queue_in_s(struct t_sqqueue *pQueue, QueueElemType *buf, int size);
int queue_out_s(struct t_sqqueue *pQueue, QueueElemType *buf, int size);
int queue_peep(struct t_sqqueue *pQueue, QueueElemType *buf, int size);

#endif /* __SqQueue_H__*/
