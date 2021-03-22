#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIZE 256
#define NUM 16
// 自己实现了一个命令行解析器：MiniShell
// 需要的知识：1、多进程编程 2、程序替换 3、C字符串操作函数 4、进程的理解
int main()
{
  // 对输入命令行字符串的解析
  char cmd[SIZE];
  const char *cmd_line = "[temp@腾讯云 MyMiniShell]# ";
  while (1)
  {
    cmd[0] = 0;
    printf("%s",cmd_line);
    fgets(cmd,SIZE,stdin);
    cmd[strlen(cmd) - 1] = '\0';//为了避免把命令的换行读进去
    char *args[NUM];           // 字符串数组  保存解析后的命令行参数，
    args[0] = strtok(cmd," ");
    int i = 1;
    do {
       args[i] = strtok(NULL," ");
       if (args[i] == NULL) break;
       ++i;
    }while(1);
    int size = sizeof(args)/sizeof(args[0]);
    args[size - 1] = NULL;

    //多进程和程序替换
    pid_t id = fork();
    if (id < 0) {
      perror("fork error!\n");
      continue;
    }
    if (id == 0) {
      // child process
      execvp(args[0],args);
      exit(1);
    }
    int status = 0;
    pid_t ret = waitpid(id,&status,0);
    if (ret > 0) {
      printf("status code : %d\n",(status >> 8) & 0xff);//这是进程退出码的底层实现，当然也可以用宏
    }else {
      printf("process wait error!\n");
    }
  }
  return 0;
}
