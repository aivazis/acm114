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

/* global variables */
long sum = 0;
pthread_mutex_t mutex;

/* worker */
void* squares(void* threadID) {
    long id = (long) threadID;
    pthread_mutex_lock(&mutex);
    sum += id;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    return NULL;
}

/* main program */
int main(int argc, char* argv[]) {
    long id;
    pthread_t threads[THREADS];
    pthread_mutex_init(&mutex, NULL);
    /* create some threads */
    for (id=0; id<THREADS; id++) {
        pthread_create(&threads[id], NULL, squares, (void*) id);
    }
    /* wait for them  to finish */
    for (id=0; id<THREADS; id++) {
        pthread_join(threads[id], NULL);
    }
    /* print the result */
    printf("sum = %ld\n", sum);
    /* exit */
    pthread_exit(NULL);
    return 0;
}
        
/* end of file */
