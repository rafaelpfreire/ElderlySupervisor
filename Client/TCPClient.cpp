#include "TCPClient.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "log.h"

#include <iostream>

using namespace std;

int connectWrapper(int socket, const struct sockaddr *address, socklen_t address_len)
{
    return connect(socket, address, address_len);
}

ssize_t sendWrapper(int sockfd, const void *buf, size_t len, int flags)
{
    return send(sockfd, buf, len, flags);
}

TCPClient::TCPClient(std::string addr, int port)
{
    this->connected = false;
    this->addr = addr;
    this->port = port;
}

TCPClient::~TCPClient()
{
    disconnect();
}

bool TCPClient::connect()
{
    if(connected)
        return true;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1)
    {
        SYSLOG_ERR("Could not create socket");
        return false;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr( addr.c_str() );

    if( connectWrapper(sock, (struct sockaddr *)&server, sizeof(server)) < 0 )
    {
        SYSLOG_ERR("Connection failed!");
        return false;
    }

    connected = true;

    return true;
}

void TCPClient::disconnect()
{
    if(connected)
    {
        close(sock);
        connected = false;
    }
}

bool TCPClient::send(std::string data)
{
    bool ret = true;

    if(!connected)
    {
        SYSLOG_ERR("Trying to send data but client is not connected");
        ret = false;
    }

    if( sendWrapper(sock, data.c_str(), strlen(data.c_str()), 0) < 0 )
    {
        SYSLOG_ERR("Failed to send message");
        ret = false;
    }

    return ret;
}

bool TCPClient::receive(std::string &rcv)
{
    bool ret = true;
    int size = 255;
    char buffer[size];

    bzero(buffer, 256);

    if(!connected)
    {
        SYSLOG_ERR("Trying to receive data but client is not connected");
        ret = false;
    }

    if( recv(sock, buffer, size, 0) < 0 )
    {
        SYSLOG_ERR("Failed to receive");
        rcv = "";
        ret = false;
    }

    rcv = std::string(buffer);

    return ret;
}
