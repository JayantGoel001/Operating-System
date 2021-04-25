#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#define BLOCKSIZE 1

int main(int argc, char *argv[]){
    int fd1,index,ret, total, index2;
    char buf,words[30];

    if(NULL == argv[1]){
        printf("Please specify the source file\n");
        exit(1);
    }

    fd1=open(argv[1],O_RDWR);

    if(fd1<0 && EBADF==errno){
        printf("Cant open File for reading and writing \n");
        perror("Opening File error");
        exit(1);
    }

    total=lseek(fd1,0,SEEK_END);
    index=0;

    while(index<total){
        lseek(fd1,index,SEEK_SET);
        read(fd1,&buf,1);
        lseek(fd1,0,SEEK_END);

        ret = write(fd1,&buf,1);
        if (-1 == ret){
            printf("File Write Error\n");
            exit(1);
        }
        index++;
    }

    printf("Input the string \n");
    fgets(words,30,stdin);

    if('\n'==words[strlen(words)-1]) {
        words[strlen(words) - 1] = '\0';
    }

    index2=0;

    while(index2<=(strlen(words)-1)){
        ret = write(fd1,&words[index2],1);
        if (-1 == ret){
            printf("File Write Error\n");
            exit(1);
        }
        index2++;
    }

    close(fd1);
    return 0;
}
