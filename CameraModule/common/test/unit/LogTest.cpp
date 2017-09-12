#include <string>
#include <syslog.h>
#include "gtest/gtest.h"
#include "hippomocks.h"
#include "log.h"


// Unit Test Fixture Class---------------------------------------------
//
class LogTest: public ::testing::Test
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
TEST_F(LogTest, SimpleUseOfTheSyslog)
{
    const std::string msg("This is a test message");

    MockRepository logMocked;
    logMocked.OnCallFunc(openlog);
    logMocked.OnCallFunc(closelog);

    SYSLOG_INFO(msg);
}
