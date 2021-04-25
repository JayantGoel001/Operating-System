#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define QUEU_SIZE 5
char queue [QUEU_SIZE] ;
int front = 0 , rear = 0 ;
int items = 0 ;
int done = 1 ;
pthread_mutex_t mutex ;
pthread_cond_t item_available ;
pthread_cond_t space_available ;

void * p_thread(){
    FILE *fp = fopen("message.txt","r");
    char c ;
    c = getc(fp);
    while (c != EOF) {
        //1
        sleep(1);
        pthread_mutex_lock (&mutex) ;
        //2
        printf ("	front<%d> rear<%d> items <%d>\n", front , rear , items ) ;
        while ( items >= QUEU_SIZE ) // while there is no space in queu to write
            pthread_cond_wait ( &space_available , &mutex ) ;
        //3
        printf ("	front<%d> rear<%d> items <%d>\n", front , rear , items ) ;
        // now we cAN write in queue
        queue [front] = c ;
        front ++ ;
        if(front==QUEU_SIZE) front = 0 ;
        items ++ ;
        printf ("	character write to queue: <%c>\n" , c ) ;
        printf ("	wake up a consumer \n" ) ;
        pthread_cond_signal(&item_available); // wake up a consumer
        pthread_mutex_unlock (&mutex) ;
        sleep (1);
        c = getc(fp);
    }
    pthread_mutex_lock (&mutex) ;
    done = 0 ; // we should tell the consumer that the file is finished
    pthread_cond_signal(&item_available);
    pthread_mutex_unlock (&mutex) ;
    fclose (fp);
    pthread_exit (0);
    return 0;
}
void * c_thread(){
    FILE* output = fopen ("message_result.txt" , "w") ;
    //4
    while ( done != 0 ) { // while there is something to read
        pthread_mutex_lock (&mutex) ;
        //5
        printf ("front<%d> rear<%d> items <%d>\n", front , rear , items ) ;
        while ( items <= 0 && done!= 0 ) // while there is no character in queu to read we should wait
            pthread_cond_wait ( &item_available , &mutex ) ;
        //6
        printf ("front<%d> rear<%d> items <%d>\n", front , rear , items ) ;

        // read the character and write it:
        char c = queue [rear] ;
        rear ++ ;
        if (rear==QUEU_SIZE) rear = 0 ;
        items -- ;
        printf ("character read from queue: <%c>\n" , c ) ;
        printf ("wake up a producer \n" ) ;
        fprintf(output,"%c",c) ;
        pthread_cond_signal(&space_available); // send signal for producer to show that thre is space
        pthread_mutex_unlock (&mutex) ;
    }
    fclose (output) ;
    pthread_exit (0);
    return 0;
}

int main()
{
	pthread_t producer , consumer;
	pthread_cond_init (&item_available, NULL) ;
	pthread_cond_init (&space_available, NULL) ;
	pthread_mutex_init (&mutex, NULL) ;
	if( pthread_create ( &producer , NULL, p_thread, NULL))  // create producer
	{
		fprintf(stderr, "Error creating producer thread\n");
		return 1;
	}
	if( pthread_create ( &consumer , NULL, c_thread, NULL))  // create the consumer
	{
		fprintf(stderr, "Error creating consumer thread\n");
		return 1;
	}
	if ( pthread_join ( producer , NULL ) ) // wait for all threads to finish
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}
	if ( pthread_join ( consumer , NULL ) )
	{
		fprintf(stderr, "Error joining consumer\n");
		return 2;
	}
	return 0;
}
