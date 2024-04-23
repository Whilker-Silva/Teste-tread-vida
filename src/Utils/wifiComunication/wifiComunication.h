#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class wifiComunication
{
private:
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

public:
    
    wifiComunication(int port);
    string receive();
    ~wifiComunication();
};

#endif /* TCPSERVER_H */
