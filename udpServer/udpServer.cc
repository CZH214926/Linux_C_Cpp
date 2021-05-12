#include "udpServer.hpp"

int main()
{
    udpServer* udp = new udpServer;

    udp->initServer();
    udp->start();

    delete udp;
    return 0;
}
