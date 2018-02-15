#include "TCPServer.h"
#include <sstream>
#include <string.h>
#include <unistd.h>
#include "log.h"

int bindWrapper(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    return bind(sockfd, addr, addrlen);
}

ssize_t sendWrapper(int sockfd, const void *buf, size_t len, int flags)
{
    return send(sockfd, buf, len, flags);
}

int listenWrapper(int sockfd, int backlog)
{
    return listen(sockfd, backlog);
}

TCPServer::TCPServer(): ssock(0), csock(0)
{
}

TCPServer::~TCPServer()
{
    disconnect(csock);
    disconnect(ssock);
}

bool TCPServer::bind(int port)
{
    ssock = socket(AF_INET, SOCK_STREAM, 0);

    if(ssock == -1)
    {
        SYSLOG_ERR("Could not create socket");
        return false;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bindWrapper(ssock, (struct sockaddr *) &server, sizeof(server)) < 0) 
    {
        SYSLOG_ERR("Could not bind");
        return false;
    }

    return true;
}

void TCPServer::disconnect(int socket)
{
    if(socket > 0)
    {
        close(socket);
        socket = 0;
    }
}

void TCPServer::disconnect()
{
    disconnect(csock);
}

bool TCPServer::listen()
{
    socklen_t clilen;

    if(ssock < 0)
    {
        SYSLOG_ERR("Server socket not binded");
        return false;
    }

    listenWrapper(ssock, 5);
    csock = accept(ssock, (struct sockaddr *) &client, &clilen);

    if (csock < 0) 
    {
        SYSLOG_ERR("ERROR on accept");
    }
    else
    {
        char ipaddr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client.sin_addr), ipaddr, INET_ADDRSTRLEN);

        std::stringstream msg;
        msg << "Connection from " << ipaddr << " stablished";
        SYSLOG_INFO(msg.str());
    }

    return true;
}

bool TCPServer::receive(std::string &rcv)
{
    bool ret = true;
    char buffer[256];

    bzero(buffer, 256);

    if((ssock > 0) && (csock > 0))
    {
        if(recv(csock, buffer, 255, 0) <= 0)
        {
            SYSLOG_ERR("Error reading from client");
            rcv = "";
            ret = false;
        }
    }
    else
    {
        SYSLOG_ERR("No connection to the client to receive message");
        ret = false;
    }

    rcv = std::string(buffer);

    return ret;
}

bool TCPServer::send(std::string msg)
{
    bool ret = false;

    if((ssock > 0) && (csock > 0))
    {
        sendWrapper(csock, msg.c_str(), strlen(msg.c_str()), 0);
        ret = true;
    }
    else
    {
        SYSLOG_ERR("No connection to the client to send message");
        ret = false;
    }

    return ret;
}
