#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include <stdlib.h>

#define BLOCKSIZE 1
#define MAX 30
#define SUCCESS 1
#define FAILURE 0

int insert_begin(int f_d)
{
    char str[MAX];
    int len = 0;
    int last_offset = 0;

    char buf = '\0';

    printf("\n Enter the string to be entered at begining:");
    memset(str , 0 , sizeof(char) * MAX);

    fgets(str , MAX , stdin);

    if('\n' == str[strlen(str) - 1]){
        str[strlen(str) - 1] = '\0';
    }

    len = strlen(str);

    printf("%d" , last_offset = lseek(f_d , -2 , SEEK_END));

    while(-1 != last_offset){
        if(read(f_d , &buf , 1) > 0){
            lseek(f_d , len - 1, SEEK_CUR);

            if(-1 == write(f_d , &buf , 1))
            {
                perror("\n write error begining");
                return FAILURE;
            }

            lseek(f_d , --last_offset , SEEK_SET);
        }else{
            perror("\n error in reading file: in insert_begin");
            return FAILURE;
        }
    }

    lseek(f_d , 0 , SEEK_SET);

    if(-1 == write(f_d , str , strlen(str))){
        printf("error in writing user string in insert_begin");
        return FAILURE;
    }

    return SUCCESS;
}

int insert_mid(int f_d , int offset) {
    char str[MAX];
    int len = 0;
    int last_offset = 0;

    char buf = '\0';

    printf("%d", last_offset = lseek(f_d, -2, SEEK_END));

    if (offset >= last_offset) {
        printf("\n offset limit reached");
        return FAILURE;
    }

    printf("\n enter the string to be entered at beginning:");
    memset(str, 0, sizeof(char) * MAX);

    fgets(str, MAX, stdin);
    if ('\n' == str[strlen(str) - 1]){
        str[strlen(str) - 1] = '\0';
    }

    len = strlen(str);

    while((offset -1) != last_offset){
        if(read(f_d , &buf , 1) > 0){
            lseek(f_d , len - 1, SEEK_CUR);
            if(-1 == write(f_d , &buf , 1)){
                perror("\n write error beginning");
                return FAILURE;
            }
            lseek(f_d , --last_offset , SEEK_SET);
        }else{
            perror("\n error in reading file: in insert_begin");
            return FAILURE;
        }
    }

    lseek(f_d , offset + 1 , SEEK_SET);

    if(-1 == write(f_d , str , strlen(str))){
        printf("error in writing user string in insert_begin");
        return FAILURE;
    }

    return SUCCESS;
}

int insert_end(int f_d)
{
    char str[MAX];
    int len = 0;
    int last_offset = 0;

    char buf = '\0';

    printf("\n enter the string to be entered at begining:");
    memset(str , 0 , sizeof(char) * MAX);

    fgets(str , MAX , stdin);

    if('\n' == str[strlen(str) - 1]) {
        str[strlen(str) - 1] = '\0';
    }
    printf("%d" , last_offset = lseek(f_d , 0 , SEEK_END));
    if(-1 == write(f_d , str , strlen(str))){
        printf("error in writing user string in insert_begin");
        return FAILURE;
    }
    return SUCCESS;
}


int main(int argc, char *argv[]){
    int fd1,fd2,ret, total,choice, offset;
    char string[30],word[30];

    memset(word,'\0',MAX);
    memset(string,'\0',MAX);

    if(NULL == argv[1]){
        printf("Please specify the first file\n");
        exit(1);
    }

    fd1=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);

    if(fd1<0 && EBADF==errno){
        printf("Cant open File for reading and writing \n");
        perror("Opening File error");
        exit(1);
    }
    if(NULL == argv[2]){
        printf("Please specify the second file\n");
        exit(1);
    }

    fd2=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);

    if(fd2<0 && EBADF==errno){
        printf("Cant open File for reading writing \n");
        perror("Opening File error");
        exit(1);
    }

    strcpy(word,"open System call");
    ret=write(fd1,word,strlen(word));

    if (-1 == ret){
        printf("File Write Error\n");
        exit(1);
    }

    strcpy(word,"write system call");
    ret=write(fd2,word,strlen(word));

    if (-1 == ret){
        printf("File Write Error\n");
        exit(1);
    }

    total=lseek(fd1,0,SEEK_END);

    ret=lseek(fd1,0,SEEK_SET);
    if(0!=ret)
        printf("seek failed to point the fd at starting \n");


    ret=lseek(fd2,0,SEEK_SET);
    if(0!=ret) {
        printf("seek failed to point the fd at starting \n");
    }

    printf("press b :to insert in beginning:\n");
    printf("press e :to insert at end:\n");
    printf("press m :to insert in somewhere middle: ");
    char ch;
    scanf("%c", &ch);

    while(getchar() != '\n');

    switch(ch){
        case 'b':
            if(SUCCESS == insert_begin(fd1))
                printf("\n inserted at beginning successfully in file 1");
            else
                printf("\n error in insertion beginning in file 1");

            if(SUCCESS == insert_begin(fd2))
                printf("\n inserted at beginning successfully in file 2");
            else
                printf("\n error in insertion beginning in file 2");

            break;

        case 'e':
            if(SUCCESS == insert_end(fd1))
                printf("\n insertion at end successful in file 1");
            else
                printf("\n error in insertion end in file 1");
            if(SUCCESS == insert_end(fd2))
                printf("\n insertion at end successful in file 2");
            else
                printf("\n error in insertion end in file 2");

            break;

        case 'm':
            printf("\n please enter the offset value:");
            scanf("%d" , &offset);
            while(getchar() != '\n');

            if(SUCCESS == insert_mid(fd1 , offset)) {
                printf("\n insertion at mid successful in file 1");
            }else {
                printf("\n insertion at mid failed in file 1");
            }
            if(SUCCESS == insert_mid(fd2 , offset)) {
                printf("\n insertion at mid successful in file 2");
            }else {
                printf("\n insertion at mid failed in file 2");
            }
            break;

        default:
            printf("\n you have entered wrong choice");
    }

    close(fd1);
    close(fd1);
    return 0;
}