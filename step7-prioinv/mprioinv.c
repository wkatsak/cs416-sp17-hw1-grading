#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "my_pthread_t.h"

#define T1_CYCLES 10*1000000
#define T2_CYCLES 1000*1000000

pthread_mutex_t lock;

void *thread1(void *arg) {
    long i=0;
    struct timeval start, end, diff;

    while (1) {
        gettimeofday(&start, NULL);
    
        pthread_mutex_lock(&lock);
        for (i=0; i<T1_CYCLES; i++)
            sqrt(3.75);
        pthread_mutex_unlock(&lock);

        gettimeofday(&end, NULL);

        timersub(&end, &start, &diff);

        printf("Thread 1: Cycle took %ld sec, %ld usec\n", diff.tv_sec, diff.tv_sec);
    }    
}

void *thread2(void *arg) {
    long i=0;
    struct timeval start, end, diff;

    while (1) {
        gettimeofday(&start, NULL);
    
        pthread_mutex_lock(&lock);
        for (i=0; i<T2_CYCLES; i++)
            sqrt(3.75);
        pthread_mutex_unlock(&lock);

        gettimeofday(&end, NULL);

        timersub(&end, &start, &diff);

        printf("Thread 2: Cycle took %ld sec, %ld usec\n", diff.tv_sec, diff.tv_sec);
    }
}

int main(){
    my_pthread_t t1, t2;
    my_pthread_mutex_init(&lock, NULL);
    
    my_pthread_create(&t1, NULL, thread1, NULL);
    my_pthread_create(&t2, NULL, thread2, NULL);

    my_pthread_join(t1, NULL);
    my_pthread_join(t2, NULL);
        
    return 0;
}
