#ifndef _LIBSSH2FACADE_H_
#define _LIBSSH2FACADE_H_

#include <string>
#include "common/log.h"

using namespace std;

class LibSSH2Facade
{
    public:
        static bool scpRead(string ip, string username, string pbKeyFilePath, string filePath);
        static bool scpWrite(string ip, string username, string pbKeyFilePath, string filePath);

    private:
        FileTransfer() {}
}

#endif // _LIBSSH2FACADE_H_
