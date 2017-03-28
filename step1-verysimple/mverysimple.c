#include <stdio.h>
#include <math.h>
#include "my_pthread_t.h"

int arg = 7;

void *thread(void *p){
    printf("Hello from thread: arg=%d\n", *(int*)p);
	return 0;
}

int main(){
    my_pthread_t t;
    int i;
    my_pthread_create(&t, NULL, thread, (void*)&arg);
    for (i=0; i<50000000; i++)
        sqrt(37.5);
        
    return 0;
}
