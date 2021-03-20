#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    int ret;
    if(argv[1]==NULL){
        printf("executable file missing \n");
        exit(1);
    }
    if(NULL==argv[2]){
        printf("executable argument missing \n");
        exit(1);
    }
    if(NULL==argv[3]){
        printf("executable argument missing \n");
        exit(1);
    }

    ret=execlp(argv[1],argv[2],argv[3],(char*)0);

    if(ret<0){
        perror("exec failed \n");
        exit(1);
    }
    return 0;
}