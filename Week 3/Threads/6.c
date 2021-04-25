#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS  3
#define TCOUNT 10
#define COUNT_LIMIT2 20

int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *inc_count(void *t){
    int i;
    long my_id = (long)t;

    for (i=0; i < TCOUNT; i++){
        pthread_mutex_lock(&count_mutex);
        count++;
        if ( count == COUNT_LIMIT2){
            printf("%d- inc_count(): thread %ld, count = %d  Threshold reached. ",i,my_id, count);
            pthread_cond_signal(&count_threshold_cv);
            printf("Just sent signal.\n");

        }
        printf("%d- inc_count(): thread %ld, count = %d, unlocking mutex\n", i,my_id, count);
        pthread_mutex_unlock(&count_mutex);

        sleep(1);
    }
    pthread_exit(NULL);
    return 0;
}

void *watch_count(void *t){
    long my_id = (long)t;

    printf("Starting watch_count(): thread %ld\n", my_id);
    pthread_mutex_lock(&count_mutex);
    while (count < COUNT_LIMIT2){
        printf("watch_count(): thread %ld Count= %d. Going into wait...\n", my_id,count);
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count(): thread %ld Condition signal received. Count= %d\n", my_id,count);
        printf("watch_count(): thread %ld Updating the value of count...%d\n", my_id,count);
        printf("watch_count(): thread %ld count now = %d.\n", my_id, count);
    }
    printf("watch_count(): thread %ld Unlocking mutex.\n", my_id);
    pthread_mutex_unlock(&count_mutex);
    sleep(1);
    pthread_exit(NULL);
    return 0;
}

int main(){
    int i, rc;
    long t[NUM_THREADS];

    for(i=0;i<NUM_THREADS;i++)
        t[i]=i+1;

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(i=0;i<NUM_THREADS;i++){
        if(i==0)
            pthread_create(&threads[i], &attr, watch_count, (void *)t[i]);
        else
            pthread_create(&threads[i], &attr, inc_count, (void *)t[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited and joined with %d threads. Final value of count = %d. Done.\n",NUM_THREADS, count);

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit (NULL);
}