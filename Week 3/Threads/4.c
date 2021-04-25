#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int g_amount = 1000;

void * th_deposit(void *th){
    pthread_mutex_lock(&mutex);
    g_amount = g_amount + 50 * 50;
    pthread_mutex_unlock(&mutex);

    return NULL;
}
void *th_withdraw(void *th){
    pthread_mutex_lock(&mutex);
    g_amount = g_amount - 20 * 20;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main(){
    pthread_t tid1 , tid2 ;
    int ret;
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
