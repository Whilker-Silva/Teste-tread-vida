#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class TCPServer
{
private:
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

public:
    // Construtor
    TCPServer(int port);

    // Função para receber dados do cliente
    std::string receive();

    // Destrutor
    ~TCPServer();
};

#endif /* TCPSERVER_H */
