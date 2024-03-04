#include "main.h"
#include "signal_handler.h"

int main(void)
{
     pid = fork();
     printf("tring to make a child process\n");

     struct sigaction act; //捕获信号API函数结构体设置
     act.sa_handler = child_signal_handler; //信号处理函数名
     sigemptyset(&act.sa_mask); //清空屏蔽信号集
     act.sa_flags = SA_RESETHAND; //处理完信号后恢复默认信号处理

     sigaction(SIGINT, &act, NULL); //调用捕获信号API函数

     /*上面这个捕获信号API函数必须放到发出信号之前*/

     while(1) //进入信号处理函数后可以返回这里
     {
          printf("I love akagi!!\n\n");
          sleep(1);
     }
     
     exit(0);
}