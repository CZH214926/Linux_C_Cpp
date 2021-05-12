#include "udpClient.hpp"

int main()
{
    udpClient* udpC = new udpClient;
    
    udpC->initClient();
    udpC->start();
    delete  udpC;
    return 0;
}
