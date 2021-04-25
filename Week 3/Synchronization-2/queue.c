#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

void check_error(int code, char *generator);

#include "queue.h"

/* global queue */
struct queue_struct thr_queue;

pthread_mutex_t queue_init_mtx = PTHREAD_MUTEX_INITIALIZER;

int queue_init(struct queue_struct *queue, int max_len) {
    if (queue == NULL)
        return EINVAL;
    /* use a lock to make sure two threads don't init the queue */
    (void) pthread_mutex_lock(&queue_init_mtx);

    /* already valid? */
    if (queue->valid == QUEUE_VALID) {
        (void) pthread_mutex_unlock(&queue_init_mtx);
        return EBUSY;
    }

    /* initialize the queue */
    (void) pthread_mutex_init(&queue->qlock, NULL);
    (void) pthread_cond_init(&queue->boss_cv, NULL);
    (void) pthread_cond_init(&queue->worker_cv, NULL);
    queue->qexit = 0;
    queue->boss_waiting = 0;
    queue->worker_waiting = 0;
    queue->queue_len = 0;
    queue->max_queue_len = max_len;
    queue->head = NULL;
    queue->tail = NULL;
    queue->valid = QUEUE_VALID;
    (void) pthread_mutex_unlock(&queue_init_mtx);

    return 0;
}

int enqueue(struct queue_struct *queue, struct q_work_struct *elem)
{
    if ((queue == NULL) || (queue->valid != QUEUE_VALID))
      return EINVAL;

    (void) pthread_mutex_lock(&queue->qlock);

    while (queue->queue_len == queue->max_queue_len) {
        queue->boss_waiting++;
        pthread_cond_wait(&queue->boss_cv, &queue->qlock);
        queue->boss_waiting--;
    }

    /* we can now add the work to the queue. */
    elem->next = NULL;
    if ( queue->queue_len == 0 ) {
        queue->head = queue->tail = elem;
    } else {
        queue->tail->next = elem;
        queue->tail = elem;
    }
    queue->queue_len++;

    /* do we have a worker to wake-up? */
    if ( queue->worker_waiting > 0 )
        (void) pthread_cond_signal(&queue->worker_cv);

    (void) pthread_mutex_unlock(&queue->qlock);
    return 0;
}

struct q_work_struct * dequeue(struct queue_struct *queue)
{
    struct q_work_struct *ptr;
    if ((queue == NULL) || (queue->valid != QUEUE_VALID))
        return NULL;
  
    (void) pthread_mutex_lock(&queue->qlock);
  
    while (queue->queue_len == 0) {
        if ( queue->qexit ) {
          (void) pthread_mutex_unlock(&queue->qlock);
          pthread_exit(NULL);
        }

        queue->worker_waiting++;
        (void) pthread_cond_wait(&queue->worker_cv, &queue->qlock);
        queue->worker_waiting--;
    }

    ptr = queue->head;
    queue->head = ptr->next;
    queue->queue_len--;
    if ( queue->queue_len == 0 )
        queue->tail = NULL;

    /* do we have any waiting boss threads? */
    if ( queue->boss_waiting > 0 )
        (void) pthread_cond_signal(&queue->boss_cv);

    (void)pthread_mutex_unlock(&queue->qlock);
    return ptr;
}
