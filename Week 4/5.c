#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include <stdlib.h>

#define BLOCKSIZE 1

int main(int argc, char *argv[])
{
    int fd1,fd2,bytesread, ret = 0, total =-1, index;
    char buf,word[30],space,end;
    space=' ';
    end='\n';

    if(NULL == argv[1]){
        printf("Please specify the source file\n");
        exit(1);
    }
    if(NULL == argv[2]){
        printf("Please specify the destination file\n");
        exit(1);
    }

    fd1=open(argv[1],O_RDONLY);

    if(fd1<0 && EBADF==errno){
        printf("Cant open File for reading \n");
        perror("Opening File error");
        exit(1);
    }

    fd2=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);

    if(fd2<0){
        if (EEXIST == errno){
            printf("Destination file exists so not overwrite\n");
            exit(1);
        }

        printf("Cant open file for writing\n");
        perror("File Writing Error");
        exit(1);
    }

    lseek(fd1,-2,SEEK_END);
    index=0;

    printf("%ld",lseek(fd1,0,SEEK_CUR));

    while(lseek(fd1,0,SEEK_CUR)!=0){
        read(fd1,&buf,1);
        word[index]=buf;
        if(buf==' '){
            while(index>0){
                ret = write(fd2,&word[index-1],1);

                if (-1 == ret){
                    printf("File Write Error\n");
                    exit(1);
                }
                index--;
            }
            write(fd2,&space,1);
            index=-1;
        }
        index++;
        lseek(fd1,-2,SEEK_CUR);
    }

    read(fd1,&buf,1);
    word[index]=buf;
    while(index>=0){
        ret = write(fd2,&word[index],1);
        if (-1 == ret){
            printf("File Write Error\n");
            exit(1);
        }

        index--;
    }
    write(fd2,&end,1);

    close(fd1);
    close(fd2);
}