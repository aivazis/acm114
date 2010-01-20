/* -*- coding: utf-8 -*-
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *                             michael a.g. aïvázis
 *                      california institute of technology
 *                      (c) 1998-2010  all rights reserved
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <pthread.h>
#include <stdio.h>
#define THREADS 10

/* worker */
void* hello(void* threadID) {
    long id = (long) threadID;
    printf("hello from %02ld/%0d!\n", id, THREADS);
    pthread_exit(NULL);
    return NULL;
}

/* main program */
int main(int argc, char* argv[]) {
    long id;
    int status;
    pthread_t threads[THREADS];
    
    for (id=0; id<THREADS; id++) {
        printf("creating thread %02ld\n", id);
        status = pthread_create(&threads[id], NULL, hello, (void*) id);
        if (status) {
            printf("error %d in pthread_create\n", status);
        }
    }

    pthread_exit(NULL);
    return 0;
}

/* end of file */
