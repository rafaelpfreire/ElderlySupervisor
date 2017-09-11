#include <string>
#include "gtest/gtest.h"
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
    SYSLOG_INFO(msg);
}
