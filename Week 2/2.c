#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    int a=10;
    int b=20;
    pid_t pid = fork();
    if (pid == 0){
        int sum = a+b;
        printf("%d",sum);
        pid = fork();
        if (pid == 0){
            int diff = a-b;
            printf("%d",diff);
            pid = fork();
            if (pid == 0){
                int mul = a*b;
                printf("%d",mul);
                pid = fork();
                if (pid == 0){
                    int div = b/a;
                    printf("%d \n ",div);
                }
            }
        }
    }else {
        printf("Parent!\n");
    }
}
