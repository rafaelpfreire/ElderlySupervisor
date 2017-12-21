#include <string>
#include <iostream>
#include "LibSSH2Facade.h"

using namespace std;

int main(int argc, char *argv[])
{
    LibSSH2Facade::SSH2_ERROR_CODE rc;
    if(argc < 8)
    {
        cout << "Usage ./scp mode(r|w) ip usr pbKey prKey fromFile toFile" << endl;
        return -1;
    }

    string mode(argv[1]);
    string ip(argv[2]);
    string usr(argv[3]);
    string pbKey(argv[4]);
    string prKey(argv[5]);
    string from(argv[6]);
    string to(argv[7]);
    string pass("");

    if(argc > 8)
        pass = argv[8];

    if(mode.compare("r") == 0)
    {
        rc = LibSSH2Facade::scpRead(ip,usr,pbKey,prKey,pass,from,to);
        if(rc != 0)
        {
            cout << "Error transfering the file. "
                 << LibSSH2Facade::str(rc) << endl;
            return -1;
        }
    }
    else
    {
        rc = LibSSH2Facade::scpWrite(ip,usr,pbKey,prKey,pass,from,to);
        if(rc != 0)
        {
            cout << "Error transfering the file. "
                 << LibSSH2Facade::str(rc) << endl;
            return -1;
        }
    }

    return 0;
}
