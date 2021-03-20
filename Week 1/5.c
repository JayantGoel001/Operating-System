#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void forkexample()
{
    pid_t pid = fork();
    if (pid == 0){
        printf("Hello from Child!\n");
    }
    else {
        printf("Hello from Parent!\n");
    }
}
int main()
{
    forkexample();
    return 0;
}
