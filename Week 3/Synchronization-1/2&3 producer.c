#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>

#define BUFFER_SIZE 10
#define CONSUMER_SLEEP_SEC 3
#define PRODUCER_SLEEP_SEC 1
#define KEY 1010

typedef struct
{
    int buff[BUFFER_SIZE];
    sem_t mutex, empty, full;

} MEM;

// Method for shared memory allocation
MEM *memory()
{
    key_t key = KEY;
    int shmid;
    shmid = shmget(key, sizeof(MEM), IPC_CREAT | 0666);
    return (MEM *) shmat(shmid, NULL, 0);
}

void init()
{
    // Initialize structure pointer with shared memory
    MEM *M = memory();

    // Initialize semaphores
    sem_init(&M->mutex,1,1);
    sem_init(&M->empty,1,BUFFER_SIZE);
    sem_init(&M->full,1,0);
}
void producer()
{
    int i=0,n;
    MEM *S = memory();

    while(1)
    {
        i++;
        sem_wait(&S->empty); // Semaphore down operation
        sem_wait(&S->mutex);
        sem_getvalue(&S->full,&n);
        (S->buff)[n] = i; // Place value to BUFFER
        printf("[PRODUCER] Placed item [%d]\n", i);
        sem_post(&S->mutex);
        sem_post(&S->full); // Semaphore up operation
        sleep(PRODUCER_SLEEP_SEC);

    }
}

int main()
{
    init();
    producer();

}