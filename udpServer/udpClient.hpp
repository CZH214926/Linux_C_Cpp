#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

class udpClient{
    private:
           std:: string _ip;
           int _port;
           int _sock;// 套接字的文件描述符
    public:
           udpClient(std::string ip = "127.0.0.1", int port = 8080)
             :_ip(ip),_port(port){}

           // 初始化客户端
           void initClient()
           {
               _sock = socket(AF_INET, SOCK_DGRAM, 0);
               std::cout << "sock : " << _sock << std::endl;
               // 客户端不需要绑定
           }

           // 启动客户端
           void start()
           {

              std :: string msg;
              struct sockaddr_in peer;
              peer.sin_family = AF_INET;
              peer.sin_port = htons(_port);
              peer.sin_addr.s_addr = inet_addr(_ip.c_str());

              while (true)
              {
                  std::cout << "Please Input# ";
                  std::cin >> msg;
                  if (msg == "quit")
                  {
                      break;
                  }
                  sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
                  char echo[128];
                  ssize_t s = recvfrom(_sock, echo, sizeof(echo) - 1, 0, nullptr, nullptr);
                  if (s > 0)
                  {
                      echo[s] = 0;
                      std::cout << "server# " << echo << std::endl;
                  }

              }
           }
           ~udpClient()
           {
             close(_sock);
           }

};
