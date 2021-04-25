#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NPROC 5
int total_num=0;
int lenght = 0 ;
pthread_mutex_t mutex ;

int n1 = 1000 , n2 = 1000;
char * s1,*s2;

int match (char *a,char *b,int pos)
{
    int i = 0;

    int lenghtb = strlen (b) - 1 ;
    int num = 0 ;
    for (i =0 ; i < lenghtb ; i++ )
        if ( a[pos+i] != '\0'  && b[i] != '\0' && a[pos+i] == b[i] )
            num ++ ;

    if ( num == lenghtb )
        return 1;
    else
        return 0;
}

void * Str_Function(void* startpos)
{
    int pos = ((int)startpos); // the position in s1 that we should start from
    printf ("my start pos is<%d>\n", pos ) ;

    int temp = 0 ;
    int i = 0 ;
    for ( i=pos; i < pos+lenght ; i++) // finding te matches
        temp += match(s1,s2, i);
    printf ("my start pos is<%d>\n", pos ) ;

    pthread_mutex_lock (&mutex) ;
    total_num += temp ; // we need the lock to cange the total_num
    printf ("total is now<%d>\n", total_num ) ;
    pthread_mutex_unlock (&mutex) ;

    //return NULL;
    pthread_exit (0);
    return 0;
}

int main(int argc, char *argv[]){
    pthread_mutex_init (&mutex, NULL) ;
    FILE *fp = fopen("strings.txt","r");
    s1 = (char*) malloc( n1 * sizeof( char* ));
    s2 = (char*) malloc( n2 *sizeof( char* ));
    fgets( s1 , n1 , fp );
    fgets( s2, n2, fp );
    n1= strlen(s1) - 1 ;
    n2= strlen(s2) - 1 ;

    lenght = n1 / NPROC ;
    printf ("s1 %s\ns2 %s \nlength to be processed by each thread %d\n", s1 , s2 , lenght);
    int i = 0 ;
    pthread_t worker[NPROC];
    for ( i =0 ; i< NPROC ; i++)
    {
        int startpos = (i* (n1/NPROC)) ;
        printf ("startpos %d\n", startpos);
        if( pthread_create ( &worker[i] , NULL, Str_Function, (void*)startpos) ) {
            fprintf(stderr, "Error creating producer thread\n");
            return 1;
        }
    }
    for ( i =0 ; i< NPROC ; i++)
    {
        if( pthread_join ( worker[i] , NULL))
        {
            fprintf(stderr, "Error creating producer thread\n");
            return 2;
        }
    }
    FILE* output = fopen ("strings_result.txt" , "w") ;
    fprintf(output,"%d",total_num) ;
    fclose(output);
}
