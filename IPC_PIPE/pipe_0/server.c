#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "./fifo"

int main()
{
    umask(0);
    //创建命名管道
    if (-1 == mkfifo(FIFO_FILE, 0666))
    {
        perror("mkfifo error");
        return 1;
    }

    // 以只读方式打开文件
    int fd = open(FIFO_FILE, O_RDONLY);
    int fd1 = open("./temp.txt",O_WRONLY | O_CREAT | O_APPEND,0644);
    dup2(fd1,1);
    close(fd1);
    if (fd >= 0)
    {
        // 开始读客户端写的数据
        char buf[64];
        while (1)
        {
            ssize_t s = read(fd, buf, sizeof(buf) - 1);
            if (s > 0)
            {
                buf[s] = 0;
                printf("client# %s",buf);
            }
            else if (s == 0)
            {
                // 通道文件被关闭
                printf("client quit,me too!\n");
                break;
            }
            else 
            {
              perror("read");
              break;
            }
        }
    }
    return 0;
}
