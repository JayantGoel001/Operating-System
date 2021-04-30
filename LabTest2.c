#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

char ar[10][100];
pthread_mutex_t lock;
void *updateString(void *arg){
    pthread_mutex_lock(&lock);
    int index = (int )arg;
    for (int i = 0; i < strlen(ar[index]); ++i) {
        ar[index][i] = toupper(ar[index][i]);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int min(int a,int b){
    if (a>b){
        return b;
    } else{
        return a;
    }
}
int main(){
    pthread_t threads[100];
    printf("Enter A string\n");
    char str[100];
    gets(str);
    printf("Enter n and m:\n");
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);

    char *token = strtok(str, " ");
    int i=0;
    while (token!=NULL){
        strcpy(ar[i++],token);
        token = strtok(NULL, " ");
    }

    for (i = 0; i < min(m,n); ++i) {
        if (pthread_mutex_init(&lock, NULL) != 0) {
            printf("\n mutex init has failed\n");
            return 1;
        }
        pthread_create(&threads[i],NULL,updateString,(void *)(i));
    }
    for (int j = m; j <n ; ++j) {
        if (pthread_mutex_init(&lock, NULL) != 0) {
            printf("\n mutex init has failed\n");
            return 1;
        }
        pthread_create(&threads[j%m],NULL,updateString,(void *)(j));
    }

    for (int j = 0; j < m; ++j) {
        pthread_join(threads[j],NULL);
    }
    pthread_mutex_destroy(&lock);
    for (int j = 0; j < n; ++j) {
        printf("%s ",ar[j]);
    }
}