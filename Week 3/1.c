#include <stdio.h>
#include <pthread.h>
void *thread(void *ptr){
    int i = (int)(ptr);
    printf("Thread %d Executing \n",i+1);
    printf("Thread ID %d\n",pthread_self());
    printf("\n");
    return 0;
}
int main(){
    pthread_t tid[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&tid[i],NULL,thread,(void *)i);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(tid[i],NULL);
    }
    return 0;
}
