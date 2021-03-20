#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
    pid_t pid;
    char buff[100],buffp[100];
    int fd[2];
    if(-1 == pipe(fd))
        perror("pipe");
    if(0 == (pid = fork()))
    {
        close(fd[1]);

        while(0 < (read(fd[0],buff,sizeof(buff))))
        {
            write(1, buff, strlen(buff));
            strtok(buff,"\n");
            if(0 ==strcmp(buff,"exit\n"))
            {
                close(fd[0]);
                break;
            }
            memset(buff, '\0',sizeof(buff));
        }

        exit(21);

    }
    else
    {
        close(fd[0]);
        while(1)
        {
            read(0, buffp, sizeof(buffp));
            write(fd[1],buffp,strlen(buffp));
            strtok(buffp,"\n");
            if(0 == strcmp(buffp,"exit"))
            {
                close(fd[1]);
                break;
            }
            memset(buffp,'\0',sizeof(buffp));
        }
    }
    wait(NULL);
    return 0;
}