#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

#include "2-queue.h"


extern struct queue_struct thr_queue;

void check_error(int code, char *generator);

int queue_terminate_workers(struct queue_struct *queue){
  if ((queue == NULL) || (queue->valid != QUEUE_VALID))
    return EINVAL;
  
  (void) pthread_mutex_lock(&queue->qlock);
  queue->qexit = 1;

  /* wakeup any waiting workers */
  (void) pthread_cond_broadcast(&queue->worker_cv);
  (void) pthread_mutex_unlock(&queue->qlock);

  return 0;
}

void queue_wait_workers(struct queue_struct *queue, int nthreads)
{
  if ((queue == NULL) || (queue->valid != QUEUE_VALID))
    return;
  
  (void) pthread_mutex_lock(&queue->qlock);
  while (queue->worker_waiting != nthreads) {
    queue->boss_waiting++;
    (void) pthread_cond_wait(&queue->boss_cv, &queue->qlock);
    queue->boss_waiting--;
  }
  (void) pthread_mutex_unlock(&queue->qlock);
}

int optimal_number_of_threads(void);
int optimal_queue_length(void);

void process_tasks()
{
#define MAX_THREADS 64
  int i, ret, nthreads, max_queue_len;
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr;
  void worker(), boss();

  nthreads = optimal_number_of_threads();
  max_queue_len = optimal_queue_length();

  /* initialize the queue */
  if ( queue_init(&thr_queue, max_queue_len) != 0 ) {
    fprintf(stderr, "queue_init() error\n");
    exit(-1);
  }

  /* initialize any special thread attributes (if needed) */
  (void) pthread_attr_init(&attr);
  /* ... */

  /* create worker threads */
  for (i = 1; (i < nthreads) && (i < MAX_THREADS); i++) {
    ret = pthread_create(&threads[i],
			 &attr,
			 (void *(*)())worker,
			 NULL);
    check_error(ret, "pthread_create()");
  }
  (void) pthread_attr_destroy(&attr);

  /* we are in the boss thread */
  boss();

  /* request the workers terminate when all work is processed */
  if ( queue_terminate_workers(&thr_queue) != 0 ) {
    fprintf(stderr, "dequeue() error\n");
    exit(-1);
  }

  /* wait for the workers to terminate */
  for (i = 1; (i < nthreads) && (i < MAX_THREADS); i++) {
    ret = pthread_join(threads[i], NULL);
    check_error(ret, "pthread_join()");
  }

  /* perform any final processing and return */
}

int get_work(struct q_work_struct* w);

void boss()
{
  struct q_work_struct *ptr;
  int ret;
  
  /* obtain work, return when complete */
  for ( ; ; ) {
    /* allocate a work structure */
    ptr = (struct q_work_struct *) malloc (sizeof(struct q_work_struct));
    if ( ptr == NULL )
      break;
    
    /* create/obtain work and fill in the work structure */
    ret = get_work(ptr);
    if ( ret == 0 ) {
      free((void *)ptr);
      break;
    }

    /* queue up the work */
    if ( enqueue(&thr_queue, ptr) != 0 ) {
      fprintf(stderr, "enqueue() error\n");
      exit(-1);
    }
  }
}

void worker()
{
  struct q_work_struct *ptr;

  for ( ; ; ) {
    /* obtain the next work request */
    ptr = dequeue(&thr_queue);
    if ( ptr == NULL ) {
      fprintf(stderr, "dequeue() error\n");
      exit(-1);
    }

    free((void *)ptr);
  }
}


  
