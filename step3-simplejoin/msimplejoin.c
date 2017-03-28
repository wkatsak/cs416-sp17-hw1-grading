#include <stdio.h>
#include <math.h>
#include "my_pthread_t.h"

#define NUM_THREADS 10

int args[NUM_THREADS];
void *retvals[NUM_THREADS];
my_pthread_t ts[NUM_THREADS];

void *thread(void *arg){
	int i=0;
	int thread_num = *(int*)arg;
	void *retval;

	printf("Hello from thread #%d\n", thread_num);
	for (i=0; i<50000000; i++)
        sqrt(37.5);

    retval = (void*) (long) (thread_num * 10);
	my_pthread_exit(retval);
}

int main(){
    int i=0;

    for (i=0; i<NUM_THREADS; i++) {
    	args[i] = i;
    	my_pthread_create(&ts[i], NULL, thread, (void*)&args[i]);   	
    }

    for (i=0; i<NUM_THREADS; i++) {
    	my_pthread_join(ts[i], &retvals[i]);
    	printf("Joined thread %d, retval %ld, expected %d\n", i, (long)retvals[i], i*10);
    }

    return 0;
}
