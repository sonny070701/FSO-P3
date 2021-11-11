#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>

int cores;
double leib = 0;

#define SIZE 2000000000

void *tfunc(void *args) {

	int tnum=*((int *) args);
	
	int inicio = tnum * (SIZE/cores);
	int fin = inicio + (SIZE/cores);
    	double leibth = 0;
    	for (int i = inicio; i < fin; i++) {
        	if (i % 2 == 0) {

            	double calc = (double)4 / ((2 * i) + 1);
            	leibth += calc;
	} else {
            	double calc = (double)-4 / ((2 * i) + 1);
            	leibth += calc;
        	}
    	}
    	leib+=leibth;
}

int main() {
    
    	long long start_ts;
    	long long stop_ts;
    	long long elapsed_time;
    	long lElapsedTime;
    	struct timeval ts;

    	pthread_t *tid;
    	int *args;

    	cores = get_nprocs();
    	tid = malloc(cores * sizeof(pthread_t));
    	args = malloc(cores * sizeof(int));

    	gettimeofday(&ts, NULL);
    	start_ts = ts.tv_sec;

    	for(int i=0;i<cores;i++) {
		args[i]=i;
		pthread_create(&tid[i],NULL,tfunc,&args[i]);
	}
	for(int i=0;i<cores;i++)
		pthread_join(tid[i],NULL);
    
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; 
    printf("Leib:  %.10lf\n", leib);
    elapsed_time = stop_ts - start_ts;
    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}