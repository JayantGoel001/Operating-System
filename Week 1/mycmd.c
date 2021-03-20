#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    if(argv[1]==NULL){
        printf("executable missing \n");
        exit(1);
    }

    if(argv[2]==NULL || argv[3]==NULL){
        printf("my executable arguments missing \n");
        exit(1);
    }

    printf("Result is %d\n",atoi(argv[1])*atoi(argv[2]));
    return 0;
}