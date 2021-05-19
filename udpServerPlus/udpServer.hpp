#pragma once 

#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class udpServer
{
    private:
          int _port;// 端口号
          int _sock; // 套接字文件描述符
          std::map<std::string, std::string> dict; // 用 map 存储字典
    public:
          udpServer(int port):_port(port),_sock(-1)
          {
              dict.insert(std::pair<std::string, std::string>("vector", "动态数组"));
              dict.insert(std::pair<std::string, std::string>("list","链表"));
              dict.insert(std::pair<std::string, std::string>("priority_queue", "优先级队列"));
              dict.insert(std::pair<std::string, std::string>("string", "字符串"));
              dict.insert(std::pair<std::string, std::string>("stack", "栈"));
              dict.insert(std::pair<std::string, std::string>("queue", "队列"));
              dict.insert(std::pair<std::string, std::string>("deque", "双端队列"));
          }
          void initServer()
          {
              _sock = socket(AF_INET, SOCK_DGRAM, 0);
              std::cout << "sock: " << _sock << std::endl; 

              struct sockaddr_in local;
              local.sin_family = AF_INET;
              local.sin_port = htons(_port);
              local.sin_addr.s_addr = INADDR_ANY;

              // 绑定
              if (bind(_sock, (struct sockaddr*)&local, sizeof(local)) < 0)
              {
                std::cerr << "bind error!\n" << std::endl;
                exit(1);
              }

          }
          void start()
          {
              char msg[64];
              for(;;)
              {
                msg[0] = '\0';
                struct sockaddr_in end_point;// 获得对端即客户端的 ip 地址 和 端口信息
                socklen_t len = sizeof(end_point);
                ssize_t s = recvfrom(_sock, msg, sizeof(msg) - 1, 0, (struct sockaddr*)&end_point, &len);
                // recvfrom : 获得客户端发来的消息，同时还要获得客户端机器的 ip 地址 和 端口号
                // 将客户端的ip和端口号打印出来
                if (s > 0)
                {
                  char buf[16];
                  sprintf(buf,"%d", ntohs(end_point.sin_port));
                  std::string cli = inet_ntoa(end_point.sin_addr);
                  cli += ":";
                  cli += buf; // ip地址 + 端口号

                  msg[s] = '\0';
                  std::cout << cli << "# " << msg << std::endl;
                  // 实现电子字典的功能
                  std::string echo = "unknow";
                  auto it = dict.find(msg);
                  if (it != dict.end())
                  {
                      echo = dict[msg];
                  }
                  // 把在服务器中找到的信息发给客户端
                  sendto(_sock, echo.c_str(),echo.size(), 0, (struct sockaddr*)&end_point, len);
                }
              }
          }
          ~udpServer()
          {
            close(_sock);
          }
};

