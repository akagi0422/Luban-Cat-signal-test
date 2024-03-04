#include "main.h"

void child_signal_handler(int sig)
{
    printf("child signal handler receve the signal successful\n");
    printf("the signal code is %d\n",sig);
    return;
}