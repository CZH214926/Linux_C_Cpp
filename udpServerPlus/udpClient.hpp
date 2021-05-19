#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class udpClient
{
    private:
          std::string _ip;
          int _port;
          int _sock;
    public:
          udpClient(std::string ip, int port)
            :_ip(ip),_port(port)
          {

          }
          void initClient()
          {
              _sock = socket(AF_INET, SOCK_DGRAM, 0);
              std::cout << "sock : " << _sock << std::endl;
          }
          void start()
          {
              struct sockaddr_in peer;
              peer.sin_family = AF_INET;
              peer.sin_port = htons(_port);
              peer.sin_addr.s_addr = inet_addr(_ip.c_str());

              std::string msg;

              for (;;)
              {
                std::cout << "Please Enter# ";
                std::cin>>msg;
                if (msg == "quit")
                {
                     break;
                }
                sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));

                char echo[128];
                ssize_t s = recvfrom(_sock, echo, sizeof(echo) - 1, 0, nullptr, nullptr);

                if (s > 0)
                {
                  echo[s] = '\0';
                  std::cout << "server# " << echo << std::endl;
                }
              }

          }
          ~udpClient()
          {
              close(_sock);
          }
};
