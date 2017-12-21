#include <sstream>
#include <fstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "LibSSH2Facade.h"
#include "log.h"




// TODO: Remove
#include <iostream>

using namespace std;

string LibSSH2Facade::str(SSH2_ERROR_CODE error)
{
    string ret;

    switch(error)
    {
    case SSH2_SUCCESS:
        ret = "SSH2_SUCCESS";
        break;
    case SSH2_SOCK_NO_CONNECTION:
        ret = "SSH2_SOCK_NO_CONNECTION";
        break;
    case SSH2_INIT_SESSION_FAIL:
        ret = "SSH2_INIT_SESSION_FAIL";
        break;
    case SSH2_SESSION_HANDSHAKE_FAIL:
        ret = "SSH2_SESSION_HANDSHAKE_FAIL";
        break;
    case SSH2_AUTHENTICATION_FAIL:
        ret = "SSH2_AUTHENTICATION_FAIL";
        break;
    case SSH2_INIT_CHANNEL_FAIL:
        ret = "SSH2_INIT_CHANNEL_FAIL";
        break;
    default:
        ret = "";
        break;
    }

    return ret;
}

void LibSSH2Facade::disconnect(LIBSSH2_SESSION *session)
{
    if(session)
    {
        libssh2_session_disconnect(session, "");
        libssh2_session_free(session);
        libssh2_exit();
    }
}

LibSSH2Facade::SSH2_ERROR_CODE LibSSH2Facade::scpRead(
        string ip,
        string username,
        string pbKeyFilePath,
        string prKeyFilePath,
        string passPhrase,
        string fromPath,
        string toPath)
{
    int sock, rc;
    struct sockaddr_in sin;
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    libssh2_struct_stat fileinfo;
    libssh2_struct_stat_size got = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    sin.sin_addr.s_addr = inet_addr(ip.c_str());

    stringstream info;
    info << "Ip: " << ip << "; Username: " << username
         << "; PubKey: " << pbKeyFilePath << "; PriKey: " << prKeyFilePath
         << "; From: " << fromPath << "; To: " << toPath;

    if( connect(sock, (struct sockaddr*)(&sin), sizeof(struct sockaddr_in)) != 0 )
    {
        stringstream msg;
        msg << "SSH2_SOCK_NO_CONNECTION. " << info.str();
        SYSLOG_ERR(msg.str());
        return SSH2_SOCK_NO_CONNECTION;
    }

    session = libssh2_session_init();
    if(!session)
    {
        stringstream msg;
        msg << "SSH2_INIT_SESSION_FAIL. " << info.str();
        SYSLOG_ERR(msg.str());
        return SSH2_INIT_SESSION_FAIL;
    }

    if( int rc = libssh2_session_handshake(session, sock) != 0 )
    {
        stringstream msg;
        msg << "SSH2_SESSION_HANDSHAKE_FAIL (ret = " << rc << "). " << info.str();
        SYSLOG_ERR(msg.str());
        return SSH2_SESSION_HANDSHAKE_FAIL;
    }

    if( libssh2_userauth_publickey_fromfile(session, username.c_str(),
                pbKeyFilePath.c_str(), prKeyFilePath.c_str(), passPhrase.c_str()) != 0 )
    {
        disconnect(session);

        stringstream msg;
        msg << "SSH2_AUTHENTICATION_FAIL. " << info.str();
        SYSLOG_ERR(msg.str());
        return SSH2_AUTHENTICATION_FAIL;
    }

    channel = libssh2_scp_recv2(session, fromPath.c_str(), &fileinfo);
    if (!channel)
    {
        disconnect(session);

        stringstream msg;
        msg << "SSH2_INIT_CHANNEL_FAIL. " << info.str();
        SYSLOG_ERR(msg.str());
        return SSH2_INIT_CHANNEL_FAIL;
    }

    ofstream outFile(toPath, ofstream::out);
    while(got < fileinfo.st_size)
    {
        char mem[1024];
        int amount=sizeof(mem);

        if((fileinfo.st_size - got) < amount)
        {
            amount = (int)(fileinfo.st_size - got);
        }

        rc = libssh2_channel_read(channel, mem, amount);
        if(rc > 0)
        {
            outFile << mem;
        }
        else if(rc < 0)
        {
            stringstream msg;
            msg << "Problem reading channel. File might be incomplete. " << info.str();
            SYSLOG_ERR(msg.str());
            break;
        }
        got += rc;
    }

    outFile.close();
    libssh2_channel_free(channel);
    channel = NULL;
    disconnect(session);

    return SSH2_SUCCESS;
}

LibSSH2Facade::SSH2_ERROR_CODE LibSSH2Facade::scpWrite(
        string ip,
        string username,
        string pbKeyFilePath,
        string prKeyFilePath,
        string passPhrase,
        string fromPath,
        string toPath)
{
    return SSH2_SUCCESS;
}
