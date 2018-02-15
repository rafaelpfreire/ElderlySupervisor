#include <string>
#include <netinet/in.h>

class TCPClient
{
    private:
        int sock;
        int port;
        bool connected;
        std::string addr;
        struct sockaddr_in server;

    public:
        TCPClient(std::string addr, int port);
        ~TCPClient();

        bool connect();
        void disconnect();
        bool send(std::string data);
        bool receive(std::string &rcv);
};
