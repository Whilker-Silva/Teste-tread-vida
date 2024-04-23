#include "TCPServer.h"

TCPServer::TCPServer(int port)
{
    // Criar o socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        cerr << "Erro ao criar o socket" << endl;
        return;
    }

    // Configurar as opções do socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        cerr << "Erro ao configurar as opções do socket" << endl;
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Vincular o socket ao endereço e porta
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        cerr << "Erro ao vincular o socket" << endl;
        return;
    }

    // Esperar por conexões
    if (listen(server_fd, 3) < 0)
    {
        cerr << "Erro ao aguardar por conexões" << endl;
        return;
    }

    cout << "Servidor aguardando por conexões na porta " << port << endl;

    // Aceitar a conexão entrante
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        cerr << "Erro ao aceitar a conexão" << endl;
        return;
    }
}

TCPServer::~TCPServer()
{
    close(new_socket);
    close(server_fd);
}

string TCPServer::receive()
{
    int valread = read(new_socket, buffer, 1024);
    return string(buffer);
}

    


