#include <iostream>
#include "TCPServer.h"

// This server can serve just one client once, and thats it

int main(int argc, char* argv[])
{
    TCPServer server;
    std::string msg;

    bool ok = true, rcv, send;

    if (server.bind(48135) == false)
    {
        std::cout << "Cannot bind to port 48135" << std::endl;
        return -1;
    }

    while( ok == true )
    {
        std::cout << "Listening on port 48135" << std::endl;
        ok = server.listen();
        rcv = send = true;

        while( (rcv == true) && (send == true) )
        {
            // loopback message
            rcv = server.receive(msg);
            std::cout << "Looping back following message: " << msg << std::endl;
            send = server.send(msg);
        }
    }

    std::cout << "Program ending" << std::endl;
    server.disconnect();

    return 0;
}
