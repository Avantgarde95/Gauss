// tools for checking each algorithm
// - correctness, exec. time, etc.

#include <math.h>
#include <sys/time.h>
#include "debug.h"

#ifndef CHECK_H
#define CHECK_H

struct timespec time_last;

/* return 'correctness' of the algorithm
 * - L2 norm of Ax-b */
double check_correct(double** A, double* b,
        double* x, int n) {
    double sq, temp;
    int i, j;

    sq = 0;

    for(i = 0; i < n; i++) {
        temp = 0;

        for(j = 0; j < n; j++) {
            temp += A[i][j] * x[j];
        }

        sq += (temp-b[i])*(temp-b[i]);
    }

    return sqrt(sq);
}

/* initialize the timer */
void init_time(void) {
    clock_gettime(CLOCK_REALTIME, &time_last);
}

/* measure the elapsed time since the last
 * call of init_time() */
double check_time(void) {
    struct timespec time_curr;
    double time_elap;

    clock_gettime(CLOCK_REALTIME, &time_curr);

    time_elap\
        = (time_curr.tv_sec - time_last.tv_sec)
        + (time_curr.tv_nsec - time_last.tv_nsec)
          / 1000000000.0;

    return time_elap;
}

#endif
