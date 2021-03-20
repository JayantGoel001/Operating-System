#include <stdio.h>
#include <unistd.h>
int main(int argc,char **argv){
    int n;
    scanf("%d",&n);
    sleep(n);
    printf("Alert!!!");
}