#include <stdio.h>

int main( int argc, char *argv[] )  {
    if( argc >= 1 ) {
        printf("Hello, welcome to Linux C programming!\n");
        printf("Number of Arguments to the main program : %d\n",argc);
        for (int i = 0; i < argc; ++i) {
            printf("Argument Number %d : %s\n",i,argv[i]);
        }
    }
    else {
        printf("One argument expected.\n");
    }
}