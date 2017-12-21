#include "gtest/gtest.h"
#include "hippomocks.h"

#include <libssh2.h>
#include "libssh2_config.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "log.h"
#include "LibSSH2Facade.h"

using namespace std;

// Unit Test Fixture Class---------------------------------------------
//
class LibSSH2FacadeTest: public ::testing::Test
{
    protected:

        string ip;
        string username;
        string pbKey;
        string prKey;
        string passPhrase;
        string fromFile;
        string toFile;

        virtual void SetUp() 
        {
            ip = "10.121.3.13";
            username = "fredy";
            pbKey = "/home/rafael/.ssh/id_rsa.pub";
            prKey = "/home/rafael/.ssh/id_rsa";
            passPhrase = "";
            fromFile = "/home/fredy/rafael/teste.txt";
            toFile = "/home/rafael/teste.txt";
        }

        virtual void TearDown()
        {
        }
};


// Test Cases ---------------------------------------------------------
//
TEST_F(LibSSH2FacadeTest, ScpReadSockNoConnection)
{
    MockRepository mock;
    mock.OnCallFunc(socket).Return(10);
    mock.OnCallFunc(inet_addr).Return(218331402);
    mock.OnCallFunc(connect).Return(-1);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    LibSSH2Facade::SSH2_ERROR_CODE errorCode = LibSSH2Facade::scpRead(
            ip, username, pbKey, prKey, passPhrase, fromFile, toFile);
    EXPECT_EQ(errorCode, LibSSH2Facade::SSH2_SOCK_NO_CONNECTION);
    EXPECT_STREQ(LibSSH2Facade::str(errorCode).c_str(), "SSH2_SOCK_NO_CONNECTION");
}

TEST_F(LibSSH2FacadeTest, ScpReadInitSessionFail)
{
    MockRepository mock;
    mock.OnCallFunc(socket).Return(10);
    mock.OnCallFunc(inet_addr).Return(218331402);
    mock.OnCallFunc(connect).Return(0);
    mock.OnCallFunc(libssh2_session_init_ex).Return(NULL);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    LibSSH2Facade::SSH2_ERROR_CODE errorCode = LibSSH2Facade::scpRead(
            ip, username, pbKey, prKey, passPhrase, fromFile, toFile);
    EXPECT_EQ(errorCode, LibSSH2Facade::SSH2_INIT_SESSION_FAIL);
    EXPECT_STREQ(LibSSH2Facade::str(errorCode).c_str(), "SSH2_INIT_SESSION_FAIL");
}

TEST_F(LibSSH2FacadeTest, ScpReadSessionHandshakeFail)
{
    LIBSSH2_SESSION *session;

    MockRepository mock;
    mock.OnCallFunc(socket).Return(10);
    mock.OnCallFunc(inet_addr).Return(218331402);
    mock.OnCallFunc(connect).Return(0);
    mock.OnCallFunc(libssh2_session_init_ex).Return(session);
    mock.OnCallFunc(libssh2_session_handshake).Return(-1);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    LibSSH2Facade::SSH2_ERROR_CODE errorCode = LibSSH2Facade::scpRead(
            ip, username, pbKey, prKey, passPhrase, fromFile, toFile);
    EXPECT_EQ(errorCode, LibSSH2Facade::SSH2_SESSION_HANDSHAKE_FAIL);
    EXPECT_STREQ(LibSSH2Facade::str(errorCode).c_str(), "SSH2_SESSION_HANDSHAKE_FAIL");
}

TEST_F(LibSSH2FacadeTest, ScpReadAuthenticationFail)
{
    LIBSSH2_SESSION *session;

    MockRepository mock;
    mock.OnCallFunc(socket).Return(10);
    mock.OnCallFunc(inet_addr).Return(218331402);
    mock.OnCallFunc(connect).Return(0);
    mock.OnCallFunc(libssh2_session_init_ex).Return(session);
    mock.OnCallFunc(libssh2_session_handshake).Return(0);
    mock.OnCallFunc(libssh2_userauth_publickey_fromfile_ex).Return(-1);
    mock.OnCallFunc(libssh2_session_disconnect_ex).Return(0);
    mock.OnCallFunc(libssh2_session_free).Return(0);
    mock.OnCallFunc(libssh2_exit);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    LibSSH2Facade::SSH2_ERROR_CODE errorCode = LibSSH2Facade::scpRead(
            ip, username, pbKey, prKey, passPhrase, fromFile, toFile);
    EXPECT_EQ(errorCode, LibSSH2Facade::SSH2_AUTHENTICATION_FAIL);
    EXPECT_STREQ(LibSSH2Facade::str(errorCode).c_str(), "SSH2_AUTHENTICATION_FAIL");
}

TEST_F(LibSSH2FacadeTest, ScpReadInitChannelFail)
{
    LIBSSH2_SESSION *session;

    MockRepository mock;
    mock.OnCallFunc(socket).Return(10);
    mock.OnCallFunc(inet_addr).Return(218331402);
    mock.OnCallFunc(connect).Return(0);
    mock.OnCallFunc(libssh2_session_init_ex).Return(session);
    mock.OnCallFunc(libssh2_session_handshake).Return(0);
    mock.OnCallFunc(libssh2_userauth_publickey_fromfile_ex).Return(0);
    mock.OnCallFunc(libssh2_session_disconnect_ex).Return(0);
    mock.OnCallFunc(libssh2_session_free).Return(0);
    mock.OnCallFunc(libssh2_scp_recv2).Return(NULL);
    mock.OnCallFunc(libssh2_exit);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    LibSSH2Facade::SSH2_ERROR_CODE errorCode = LibSSH2Facade::scpRead(
            ip, username, pbKey, prKey, passPhrase, fromFile, toFile);
    EXPECT_EQ(errorCode, LibSSH2Facade::SSH2_INIT_CHANNEL_FAIL);
    EXPECT_STREQ(LibSSH2Facade::str(errorCode).c_str(), "SSH2_INIT_CHANNEL_FAIL");
}
