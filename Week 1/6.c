#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;
    int status;
    int *ptr=NULL;
    int expression;
    pid=fork();

    if(0==pid){
        printf(" child process is running \n");
        printf("child parent %d\n",getppid());
        printf("child  id %d\n",getpid());
        printf("child  gets value of pid -->%d\n",pid);
        exit(10);
    }
    else{
        wait(&status);
        printf("parent process is running \n");
        printf("parent parent id is %d\n",getppid());
        printf("parent id %d\n",getpid());
        printf("parent child pid %d\n",pid);
        if(WIFEXITED(status)) {
            printf("child process %d exit status %d \n", pid, WEXITSTATUS(status));
        }
    }
    return 0;
}