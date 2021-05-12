.PHONY:all
all:udpClient udpServer

udpServer:udpServer.cc
	g++ -o $@ $^ -std=c++11
udpClient:udpClient.cc 
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f udpClient udpServer 

