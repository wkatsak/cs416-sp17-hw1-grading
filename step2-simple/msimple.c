#include <stdio.h>
#include <math.h>
#include "my_pthread_t.h"

int arg = 7;

void *thread(void *p){
	printf("Hello from thread: arg=%d\n", *(int*)p);
	my_pthread_exit(0);
}

int main(){
    my_pthread_t t;
    int i=0;
    double num = 3.14;
    my_pthread_create(&t, NULL, thread, (void*)&arg);   
    for (i=0; i<50000000; i++,num+=1.0)
        sqrt(num);

    return 0;
}
