#include "udpClient.hpp"
using namespace std;

void Usage(string s)
{
    cout << s << endl << "\t" << "server_ip server_port" << endl;
}
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
      Usage(argv[0]);
      exit(1);
    }
    udpClient udp(argv[1], stoi(argv[2]));
    udp.initClient();
    udp.start();
    return 0;
}
