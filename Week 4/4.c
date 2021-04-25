#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include <stdlib.h>
#define BLOCKSIZE 1

int main(int argc, char *argv[])
{
    int fd1,fd2,bytesread, ret = 0, total =-1, n, value;
    char buf[BLOCKSIZE];

    if(NULL == argv[1]){
        printf("Please specify the source file\n");
        exit(1);
    }
    if(NULL == argv[2]){
        printf("Please specify the destination file\n");
        exit(1);
    }

    fd1 = open(argv[1],O_RDONLY);
    if(fd1<0 && EBADF==errno){
        printf("Cant open File for reading \n");
        perror("Opening File error");
        exit(1);
    }

    fd2 = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,S_IRWXU);

    if(fd2<0){
        if (EEXIST == errno){
            printf("Destination file exists so not overwrite\n");
            exit(1);
        }
        printf("Cant open file for writing\n");
        perror("File Writing Error");
        exit(1);
    }

    printf("Enter the value of N\n");
    scanf("%d",&n);
    value=1;

    while((bytesread = read(fd1,buf,BLOCKSIZE))>0){
        if(value%n==1){
            ret = write(fd2,buf,bytesread);
            if (-1 == ret){
                printf("File Write Error\n");
                exit(1);
            }
            total = total + ret;
        }
        value++;
    }

    if ( total  > 0){
        printf("Written Successfully %d bytes\n", total);
    }else{
        printf("Error/Zero Byte  case\n");
    }

    close(fd1);
    close(fd2);
}
