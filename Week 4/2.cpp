#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
pthread_mutex_t outlock;
int nsteps, maxsteps = 0;
int eat_count[NTHREADS];
void trace(int i, char *s) {
    pthread_mutex_lock(&outlock);
    if (strcmp (s, "eating") == 0) eat_count [i]++;
    if (nsteps++ > maxsteps) {
        if (strcmp(s,"thinking") == 0) {
            pthread_mutex_unlock(&outlock);
            pthread_exit(0);
        }
    }
    pthread_mutex_unlock(&outlock);
}
void * philosopher_body(void *arg) {
    int self = *(int *) arg;
    for (;;) {
        trace(self,"thinking");
        chopsticks_take(self);
        trace(self,"eating");
        chopsticks_put(self);
    }
}
int main() {
    int i;
    pthread_t th[NTHREADS]; /* IDs of the philospher threads */
    int no[NTHREADS]; /* corresponding table position numbers*/
    pthread_attr_t attr;
    for (i = 0; i < NTHREADS; i++) eat_count [i] = 0;
    pthread_mutex_init(&outlock, NULL);
    chopsticks_init();
    fprintf(stdout,"enter number of steps to run: "); fflush(stdout);
    fscanf(stdin,"%d",&maxsteps);
    pthread_attr_init (&attr); /* sets default attributes */
    pthread_setconcurrency (4);
    pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
    for (i = 0; i < NTHREADS; i++) {
        no[i] = i;
        pthread_create(&th[i], NULL, philosopher_body, (int *) &no[i]);
    }
    for (i = 0; i < NTHREADS; i++) pthread_join(th[i], NULL);
    for (i = 0; i < NTHREADS; i++) {
        fprintf (stderr, "philosopher %d ate %d times\n", i, eat_count [i]);
    }
    return 0;
}