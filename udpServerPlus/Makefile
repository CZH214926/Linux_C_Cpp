FLAG = -std=c++11
.PHONY:all
all:udpClient udpServer

udpServer:udpServer.cc
	g++ -o $@ $^ $(FLAG)
udpClient:udpClient.cc 
	g++ -o $@ $^ $(FLAG)

.PHONY:clean
clean:
	rm -rf udpClient udpServer 
