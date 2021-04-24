#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
// char buf[1024];
// 用一个全局缓冲区的方式是不可能实现进程间的通信的，因为会有写时拷贝，到时候这个全局缓冲区就不是2个进程公有的了

int main()
{
     int pipefd[2] = {0}; //输出型参数
     pipe(pipefd);
     printf("pipefd[0] = %d, pipefd[1] = %d\n",pipefd[0],pipefd[1]);
     //用fork创建子进程
     //子进程去写数据，父进程去读数据
     pid_t id = fork();
     if (id < 0)
     {
       perror("create child process error!\n");
       return 1;
     }
     if (id == 0)
     {
       // This is child process
       // 子进程用来写数据
       close(pipefd[0]);
       const char* msg = "Hello father,I am zhihao.\n";
       while (1)
       {
         write(pipefd[1],msg,strlen(msg));
         //sleep(1);
       }
     }
     else 
     {
        // This is father process
        // 父进程用来读数据
        // 当管道中没有数据的时候===>1、子进程写入数据的速度没有父进程读取速度快  2、子进程不再写入  读数据的进程会阻塞
        // 状态也有 R+ 到 S+
        close(pipefd[1]);
        char buffer[64];
        int count = 0;
        while (1)
        {
           ssize_t len =  read(pipefd[0], buffer, sizeof(buffer) - 1);
           if (len > 0)
           {
                buffer[len] = 0;
                printf("I(father) get your message : %s\n",buffer);
                sleep(2);
           }

//           if (count++ == 4)
//           {
//               close(pipefd[0]);
//               break;
//           }
        }
        int status = 0;
        waitpid(id,&status,0);
        printf("child process get a signal, and signal number is : %d\n",status & 0x7f);
     }

    return 0;
}
