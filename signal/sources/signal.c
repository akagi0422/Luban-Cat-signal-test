// 创建子进程
// 父进程随便干点啥,比如waiting for signal
// 子进程设个闹钟,进入自创的信号处理函数printf一下
// 子进程利用kill函数向父进程发送信号
// 父进程处理,kill子进程回收资源
// 退出

#include "main.h"
#include "signal_handler.h"

int main(void)
{
     printf("tring to make a child process\n");
     pid = fork();

     if(pid == -1)
     {
          printf("fork error\n");
     }
     else if(pid == 0)
     {
          child_pid = getpid();

          struct sigaction act; //捕获信号API函数结构体设置
          act.sa_handler = child_signal_handler; //信号处理函数名
          sigemptyset(&act.sa_mask); //清空屏蔽信号集
          act.sa_flags = SA_RESETHAND; //处理完信号后恢复默认信号处理

          sigaction(14, &act, NULL); //调用捕获信号API函数

          /*上面这个捕获信号API函数必须放到发出信号的函数之前*/
          /*比如在这里就必须放到alarm()之前*/

          printf("this is child process, the pid is %d\n",child_pid); //子进程测试闹钟
          printf("testing for alarm\n");
          second = alarm(2);
          printf("last alarm have %d seconds\nsleep 1s!\n",second);
          sleep(1);
          printf("woke up, reset alarm to 1s\n");
          second = alarm(1);
          printf("last alarm have %d seconds\n\n",second);
          sleep(1); //只要注册了信号，不论睡眠多长时间都可以捕捉

          //进入信号处理函数后不返回这里,但还能正常退出？？？//
          /*信号处理函数处理完一次alarm就会恢复默认处理方式*/
          /*在信号处理函数中向父进程发送alarm会触发默认处理方式*/
          /*导致子进程异常退出*/
          /*由于下列语句由于延时1s等待闹钟，时序上在收到信号后，所以不会执行*/
          /*如果不延时1s，子进程中语句将执行到alarm响起时刻*/
          printf("I love akagi!!\n\n");
          sleep(1);
          printf("I love akagi!!\n\n");
          sleep(1);

          exit(0);
     }
     else
     {
          sleep(1);

          father_pid = getpid();
          printf("this is father process, the pid is %d\n",father_pid);

          struct sigaction act; //捕获信号API函数结构体设置
          act.sa_handler = father_signal_handler; //信号处理函数名
          sigemptyset(&act.sa_mask); //清空屏蔽信号集
          act.sa_flags = SA_RESETHAND; //处理完信号后恢复默认信号处理

          // chidl_pid = wait(&status); //等待子进程结束 先等待子进程结束会进入信号14的中断，不会进入信号处理函数

          sigaction(14, &act, NULL); //调用捕获信号API函数

          printf("father is ready for catch alarm\n\n");

          child_pid = wait(&status); //为什么返回值是-1——子进程被第二个中断杀了，异常退出
          // child_pid = waitpid(pid, &status, 0); //等待子进程结束，为什么返回值是-1——子进程被第二个中断杀了，异常退出

          if(child_pid == pid) //捕获到信号后能返回这里继续执行
          {
               printf("child process was exit, the exit code is %d\n",status);
          }
          else
          {
               printf("child process exit error, the exit code is %d\nchild pid is %d\n",status, child_pid);
          }

          exit(0);
     }
}