#include <zephyr.h>
#include "display.h"

#define MY_STACK_SIZE 512
#define MY_PRIORITY 7

/* declare thread at compile time */
K_THREAD_DEFINE(display_tid, MY_STACK_SIZE,
                display_main, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);
