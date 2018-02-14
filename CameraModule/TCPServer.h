#include <string>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TCPServer
{
    public:
        TCPServer();
        ~TCPServer();

        bool bind(int port);
        bool listen();
        bool receive(std::string &rcv);
        bool send(std::string msg);
        void disconnect();

    protected:
        void disconnect(int socket);

        int ssock;
        int csock;
        struct sockaddr_in server;
        struct sockaddr_in client;
};
