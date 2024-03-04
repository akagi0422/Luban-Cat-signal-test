#include "main.h"

void child_signal_handler(int sig)
{
    printf("child signal handler receve the signal successful\n");
    printf("the signal code is %d\n",sig);
    kill(father_pid,14); //向父进程发送信号
    printf("already alarm the father process\nchild process task is finish!\n\n");
    return;
    /*信号处理函数处理完一次alarm就会恢复默认处理方式*/
    /*在信号处理函数中向父进程发送alarm会触发默认处理方式*/
    /*导致子进程异常退出，不会执行主函数中收到信号后的语句*/
}

void father_signal_handler(int sig)
{
    printf("father signal handler receve the signal successful\n");
    printf("receve signal code %d\n",sig);
    printf("father process task is finish!\n\n");
    return;
}