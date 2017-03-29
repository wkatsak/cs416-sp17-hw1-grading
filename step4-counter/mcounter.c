#include <stdio.h>
#include <stdlib.h>
#include "my_pthread_t.h"

#define ITER 5000000

my_pthread_mutex_t lock;
int c = 0;

void* counter(void *arg){
	int i, temp;
	for(i=0; i<ITER; i++){
		my_pthread_mutex_lock(&lock);		
		temp = c;
		temp++;
		c = temp;
		my_pthread_mutex_unlock(&lock);
	}

	my_pthread_exit(0);
}

int main(int argc, char* argv[]){
    my_pthread_t *ts;
    int num_threads = 2;
    int tmp , i;

    if (argc == 2) {
        tmp = atoi(argv[1]);
        if (tmp > 0)
            num_threads = tmp;
    }

    // Malloc space for threads
    ts = (my_pthread_t *) malloc(sizeof(my_pthread_t) * num_threads);

    // initialize lock
    if (my_pthread_mutex_init(&lock, NULL) !=0)
    {
        printf("mutex init failed\n");
        exit(1);
    }

    // create threads
    for(i=0; i<num_threads; i++){
        my_pthread_create(&ts[i], NULL, counter, NULL);
    }
    
    // join threads
    for(i=0; i<num_threads; i++){
	    my_pthread_join(ts[i], NULL);
    }

	printf("counter final val: %d, expecting %d\n", c, ITER * num_threads);
	return 0;
}
