#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>

sem_t  posixsema;

int g_amount = 1000;
void * th_deposit(void *th){
    sem_wait(&posixsema);
    g_amount = g_amount + 50 * 50;
    sem_post(&posixsema);
    return NULL;
}

void *th_withdraw(void *th){
    sem_wait(&posixsema);
    g_amount = g_amount - 20 * 20;
    sem_post(&posixsema);
    return NULL;
}
int main(){
    pthread_t tid1 , tid2 ;
    int ret;

    ret = sem_init(&posixsema,0,1);
    if (-1 == ret){
        printf("Failed to initialise Semaphore\n");
        exit(1); //Exit the Process
    }
    if(0 != pthread_create(&tid1 , NULL , th_deposit , NULL)){
        perror("error in deposit thread");
        exit(1);
    }

    if(0 != pthread_create(&tid2 , NULL , th_withdraw , NULL)){
        perror("error in deposit thread");
        exit(1);
    }

    pthread_join(tid1 , NULL);
    pthread_join(tid2 , NULL);

    printf("amount after transaction is : %d", g_amount);
    return 0;
}
