// the flags for turning debugging on/off

#ifndef DEBUG_H
#define DEBUG_H

#define TRUE 1
#define FALSE 0

int ENABLE_DEBUG = TRUE;

/* turn on debugging */
void enable_debug(void) {
    ENABLE_DEBUG = TRUE;
}

/* turn off debugging */
void disable_debug(void) {
    ENABLE_DEBUG = FALSE;
}

#endif
