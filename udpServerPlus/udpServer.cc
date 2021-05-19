#include "udpServer.hpp"

using namespace std;
void Usage(string proc)
{
  cout << "Usage: " << proc << " port" << endl;
}
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
      Usage(argv[0]);
      exit(1);
    }
    udpServer *udp = new udpServer(stoi(argv[1]));
    udp->initServer();
    udp->start();

    delete udp;

    return 0;
}
