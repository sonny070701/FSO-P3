#define _GNU_SOURCE    
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/sysinfo.h>

#define SIZE 2000000000
#define FIBER_STACK 1024*64

int cores;
double leib = 0;

int cloneFunc (void* args) {
	
	int NHILO = *((int *) args);
	int inicio = NHILO * (SIZE/cores);
	int fin = inicio + (SIZE/cores);
    	double leibth = 0;

   	for (int i = inicio; i < fin; i++) {
        	if (i % 2 == 0) {
            		double calc = (double)4 / ((2 * i) + 1);
            		leibth += calc;
			}
        	else {
           		double calc = (double)-4 / ((2 * i) + 1);
            		leibth += calc;
        	}
    	}
    	leib+=leibth;
	exit(0);
}

int main() {

	long long start_ts;
    	long long stop_ts;
    	long long elapsed_time;
    	long lElapsedTime;
    	struct timeval ts;

	pid_t pid;
	int status;
	int* param;
	int i;
	void* stack;

	cores = get_nprocs();
	
    	pid = malloc(cores * sizeof(pid_t));
    	param = malloc(cores * sizeof(int));

    	gettimeofday(&ts, NULL);
    	start_ts = ts.tv_sec;

	stack = malloc(FIBER_STACK* cores);
	if ( stack == 0 ){
		perror("error");
		exit(1);
	}
	
	for(i = 0; i < cores; i++) {
		param[i] = i;
		pid = clone(cloneFunc,(char*) stack + FIBER_STACK*(i+1), 
				SIGCHLD |CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM, &param[i]);
		if (pid == -1) {
			perror("clone");
			exit(2);
		}
	}
	for(i = 0; i < cores; i++) {
		pid=wait(&status);
		if ( pid == -1 ) {
			perror( "waitpid" );
			exit( 3 );
		}
	}
    
    	gettimeofday(&ts, NULL);
    	stop_ts = ts.tv_sec; 
    	printf("Leib:  %.10lf\n", leib);
    	elapsed_time = stop_ts - start_ts;
    	printf("------------------------------\n");
    	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
	free( stack );
        
	return 0;
}