#include "parentThread.h"
#include "childThread.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "misc.h"

#define NUM_THREADS 4
#define NUM_ARGUMENTS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main(int argc, char* argv[])
{
    struct threadData data;
    int delay = atoi(argv[2]);
    int solArray[9][9];
    int i;

    pthread_t pthreads[NUM_THREADS];

    /* If number of arguments is valid */
    if(argc == NUM_ARGUMENTS) 
    {  
        processFile(solArray, 9, 9, argv[1]); 
        initialiseStruct(&data, delay, solArray);

        /* Create the children threads */
        pthread_create(&pthreads[0], NULL, threadOneFunc, (void*)&data);
        pthread_create(&pthreads[1], NULL, threadTwoFunc, &data);
        pthread_create(&pthreads[2], NULL, threadThreeFunc, &data);
        pthread_create(&pthreads[3], NULL, threadFourFunc, &data);
        
        /* Wait for Child threads to finish before parent can access data*/
        pthread_mutex_lock(&mutex);
        while(data.numFinishedThreads < 4)
        {
            pthread_cond_wait(&cond, &mutex);
        }
    
        printResults(&data);
        pthread_mutex_unlock(&mutex);


        /* Release child thread resources */
        for(i=0; i<NUM_THREADS; i++)
        {
        pthread_join(pthreads[i], NULL);
        }

    }
    else
    {
        printf("Invalid number of arguments given. Goodbye!");
    }

    return (0);
}