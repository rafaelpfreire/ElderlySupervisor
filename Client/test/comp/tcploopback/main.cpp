#include <iostream>
#include <vector>
#include <unistd.h>
#include "TCPClient.h"

std::string randomStr(const int len);
int sendAndCheck(std::vector<std::string> vector, TCPClient &clt);

int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        std::cout << "Usage: ./program <ip>" << std::endl;
        return -1;
    }

    int errors = 0;
    std::vector<std::string> smsg5, rmsg5;
    std::vector<std::string> smsg10, rmsg10;
    std::vector<std::string> smsg20, rmsg20;
    std::vector<std::string> smsg100, rmsg100;

    std::string ip = argv[1];
    TCPClient client(ip, 48135);

    // Creating random strings
    for(int i = 0; i < 10; i++)
    {
        smsg5.push_back(randomStr(5));
        smsg10.push_back(randomStr(10));
        smsg20.push_back(randomStr(20));
        smsg100.push_back(randomStr(100));
    }

    if(client.connect())
    {
        errors += sendAndCheck(smsg100, client);
        errors += sendAndCheck(smsg5, client);
        errors += sendAndCheck(smsg10, client);
        errors += sendAndCheck(smsg20, client);
    }
    else
    {
        std::cout << "Not able to connect to server" << std::endl;
    }

    std::cout << "Number of errors of the test: " << errors << std::endl;

    return 0;
}

std::string randomStr(const int len)
{
    char str[len+1];
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < len; i++)
    {
        str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    str[len] = '\0';
    return std::string(str);
}

int sendAndCheck(std::vector<std::string> vector, TCPClient &clt)
{
    int i = 0;
    int errors = 0;
    std::string rcv;
    std::vector<std::string>::iterator it;

    std::cout << "Sending strings of size " << vector.at(0).length() << std::endl;
    for(it = vector.begin(); it != vector.end(); it++)
    {
        if(clt.send(*it) == false)
        {
            errors++;
            std::cout << "Problem sending message " << i << ": " << *it << std::endl;
            std::cout << "Ending program" << std::endl;
            break;
        }

        i++;
        clt.receive(rcv);
    
        if(*it != rcv)
        {
            errors++;
            std::cout << "ERROR: Message sent: " << *it
                << " Message received: " << rcv << std::endl;
        }

        usleep(100000);
    }

    return errors;
}
