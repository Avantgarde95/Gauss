#include <stdlib.h>
#include <time.h>
#include "debug.h"

#ifndef RAND_H
#define RAND_H

/* initialize drand48
 * - If ENABLE_DEBUG is false,
 *   it sets the seed to the current time */
void init_rand(void) {
    if(ENABLE_DEBUG) {
        srand48(100);
    }
    else{
        srand48(time(NULL));
    }
}

/* select a number randomly in [0, 1) */
double select_rand(void) {
    return (0.001+drand48()) * 0.999;
}

#endif
