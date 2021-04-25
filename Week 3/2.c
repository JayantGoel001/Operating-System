#include <stdio.h>
#include <pthread.h>
#include<string.h>

struct Person{
    char name[100];
    int hallNo;
    int id;
    int branch;
};
void *thread(void *ptr){
    struct Person *p = (struct Person*)(ptr);
    printf("Name : %s Hall No:%d ID: %d Branch: %d",p->name,p->hallNo,p->id,p->branch);
    printf("\n");
    return 0;
}
int main(){
    pthread_t tid[2];
    struct Person p[2];
    strcpy(p[0].name, "Jayant");
    p[0].hallNo = 1;
    p[0].id = 0;
    p[0].branch = 132;

    strcpy(p[1].name, "Antman");
    p[1].hallNo = 2;
    p[1].id = 1;
    p[1].branch = 3290;

    for (int i = 0; i < 2; i++) {
        pthread_create(&tid[i],NULL,thread,&p[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(tid[i],NULL);
    }
    return 0;
}
