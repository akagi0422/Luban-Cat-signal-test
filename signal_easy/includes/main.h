#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;
pid_t child_pid;
pid_t father_pid;
int second;
int status;