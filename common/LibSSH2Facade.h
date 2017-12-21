#ifndef _LIBSSH2FACADE_H_
#define _LIBSSH2FACADE_H_

#include <string>
#include <libssh2.h>
#include "libssh2_config.h"

using namespace std;

class LibSSH2Facade
{
    public:

        enum SSH2_ERROR_CODE
        {
            SSH2_SUCCESS = 0,
            SSH2_SOCK_NO_CONNECTION = -1,
            SSH2_INIT_SESSION_FAIL = -2,
            SSH2_SESSION_HANDSHAKE_FAIL = -3,
            SSH2_AUTHENTICATION_FAIL = -4,
            SSH2_INIT_CHANNEL_FAIL = -5
        };

        static string str(SSH2_ERROR_CODE error);

        static SSH2_ERROR_CODE scpRead(
                string ip,
                string username,
                string pbKeyFilePath,
                string prKeyFilePath,
                string passPhrase,
                string fromPath,
                string toPath);

        static SSH2_ERROR_CODE scpWrite(
                string ip,
                string username,
                string pbKeyFilePath,
                string prKeyFilePath,
                string passPhrase,
                string fromPath,
                string toPath);

    protected:
        static void disconnect(LIBSSH2_SESSION *session);

    private:
        LibSSH2Facade() {}
};

#endif // _LIBSSH2FACADE_H_
