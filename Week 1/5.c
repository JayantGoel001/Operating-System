#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void forkexample()
{
    pid_t pid = fork();
    if (pid == 0){
        printf("Hello from Child! : %d \n ",pid);
    }
    else {
        printf("Hello from Parent! : %d \n",pid);
    }
}
int main()
{
    forkexample();
    return 0;
}
