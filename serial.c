#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define SIZE 2000000000

int main() {

    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    double leib = 0;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec;

    for (int i = 0; i < SIZE; i++) {

        if (i % 2 == 0) {

            double calc = (double)4 / ((2 * i) + 1);
            leib += calc;
        }
        else {
            double calc = (double)-4 / ((2 * i) + 1);
            leib += calc;
        }
    }
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; 
    printf("Leib:  %.10lf\n", leib);
    elapsed_time = stop_ts - start_ts;
    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}