#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int ret;
    pid_t pid;
    int choice;
    printf("1: part A of question\n");
    printf("2: part B of question\n");
    printf("3: part C of question\n");
    printf("4: part D of question\n");
    
    scanf("%d",&choice);
    
    if (choice==1) {
        pid = fork();
        if (pid == 0) {
            printf("Child Process \n");
            ret = execlp("./pgm2", "pgm2", "10", "20", (char *) 0);
            if (ret < 0) {
                perror("exec failed \n");
                exit(1);
            }
        } else {
            printf("Parent Process \n");
        }
    }
    if (choice==2) {
        ret = execlp("./PGM2", "PGM2", "10", "20", (char *) 0);
        if (ret < 0) {
            perror("exec failed \n");
            exit(1);
        }
        pid = fork();

        if (pid == 0) {
            printf("Child Process \n");
        } else {
            printf("Parent Process \n");
        }
    }
    if (choice==3) {
        pid = fork();
        ret = execlp("./PGM2", "PGM2", "10", "20", (char *) 0);
        if (pid == 0) {
            printf("Child Process \n");
        } else {
            printf("Parent Process \n");
        }
    }
    if (choice==4) {
        pid = fork();
        if (pid == 0) {
            printf("Child Process \n");
        } else {
            printf("Parent Process \n");
            ret = execlp("./PGM2", "PGM2", "10", "20", (char *) 0);
            if (ret < 0) {
                perror("exec failed \n");
                exit(1);
            }
        }
    }
}
