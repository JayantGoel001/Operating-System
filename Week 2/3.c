#include <stdio.h>
#include <signal.h>

void sigint(int sigint){
    printf("CHILD: I have received a SIGINT%d\n", sigint);
}
int main(int argc,char **argv){
    int pid = fork();
    if ( pid< 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0){
        signal(SIGINT,sigint);
        for(;;);
    }else{
        printf("PARENT: sending SIGINT\n\n");
        kill(pid,SIGINT);
    }
}