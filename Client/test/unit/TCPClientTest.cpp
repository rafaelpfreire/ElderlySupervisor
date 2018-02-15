#include "gtest/gtest.h"
#include "hippomocks.h"
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "TCPClient.h"


// Unit Test Fixture Class---------------------------------------------
//
class TCPClientTest: public ::testing::Test
{
    protected:

        virtual void SetUp() 
        {
        }

        virtual void TearDown()
        {
        }
};


// Test Cases ---------------------------------------------------------
//
TEST_F(TCPClientTest, ConnectionSuccess)
{
    MockRepository mock;
    mock.OnCallFunc(socket).Return(3);
    mock.OnCallFunc(connect).Return(0);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    TCPClient client("10.0.0.10", 4000);
    EXPECT_TRUE(client.connect());
}

TEST_F(TCPClientTest, ConnectionSocketFail)
{
    MockRepository mock;
    mock.OnCallFunc(socket).Return(-1);
    mock.OnCallFunc(connect).Return(0);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    TCPClient client("10.0.0.10", 4000);
    EXPECT_FALSE(client.connect());
}

TEST_F(TCPClientTest, ConnectionFail)
{
    MockRepository mock;
    mock.OnCallFunc(socket).Return(3);
    mock.OnCallFunc(connect).Return(-1);
    mock.OnCallFunc(openlog);
    mock.OnCallFunc(closelog);

    TCPClient client("10.0.0.10", 4000);
    EXPECT_FALSE(client.connect());
}
