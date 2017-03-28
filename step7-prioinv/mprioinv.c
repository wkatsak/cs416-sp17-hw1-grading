#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "my_pthread_t.h"

#define T1_CYCLES 10*1000000
#define T2_CYCLES 100*1000000

pthread_mutex_t lock,lock2;
int flag=0;

void *thread1(void *arg) {
    long i=0;
    struct timeval start, end, diff;
	int count =0;
	double num=3.14;

	//dont do any work until we're sure t2 is demoted to lower priority
	while (1){
		my_pthread_mutex_lock(&lock);
		if (flag==1){
			my_pthread_mutex_unlock(&lock);	
			break;
		}
		my_pthread_mutex_unlock(&lock);	
	}

	//my_pthread_mutex_lock(&lock2);
	/*while(1){
		num =3.14;
		for(i=0;i<T2_CYCLES;i++,num++)
			sqrt(num);
		printf("thread 1: im running\n");
	}
*/
	my_pthread_mutex_unlock(&lock2);

   	while (count<10) {
		++count;
        gettimeofday(&start, NULL);
    	//on my system each for loop takes ~60-75ms
		//which is more than the scheduling quantum
        pthread_mutex_lock(&lock);
        for (i=0; i<T2_CYCLES; i++,num++)
			sqrt(num);
        pthread_mutex_unlock(&lock);

        gettimeofday(&end, NULL);

        timersub(&end, &start, &diff);

        printf("Thread 1: Cycle took %ld sec, %ld usec\n", diff.tv_sec, diff.tv_sec);
    }
		
}

void *thread2(void *arg) {
    long i=0;
    struct timeval start, end, diff;
	int count =0;
	double num = 3.14;
    while (count<10) {
        gettimeofday(&start, NULL);
   		++count; 
        pthread_mutex_lock(&lock);
        for (i=0; i<T2_CYCLES; i++,num++)
            sqrt(num);
        pthread_mutex_unlock(&lock);
		
        gettimeofday(&end, NULL);

        timersub(&end, &start, &diff);

        printf("Thread 2: Cycle took %ld sec, %ld usec\n", diff.tv_sec, diff.tv_sec);
		my_pthread_mutex_lock(&lock);
		//my_pthread_mutex_lock(&lock2);
		flag = 1;
		my_pthread_mutex_unlock(&lock);
	}

/*	while(1){
		num =3.14;
		for(i=0;i<T2_CYCLES;i++,num++)
			sqrt(num);
		printf("thread 2: im running\n");
	}
*/

}


int main(){
    my_pthread_t t1, t2;
    my_pthread_mutex_init(&lock, NULL);
    my_pthread_mutex_init(&lock2, NULL);
    
    my_pthread_create(&t1, NULL, thread1, NULL);
    my_pthread_create(&t2, NULL, thread2, NULL);

    my_pthread_join(t1, NULL);
    my_pthread_join(t2, NULL);
        
    return 0;
}
