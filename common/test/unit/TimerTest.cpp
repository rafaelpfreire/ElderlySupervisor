#include <chrono>
#include "gtest/gtest.h"
#include "hippomocks.h"
#include "Timer.h"


using namespace std::chrono;

// Unit Test Fixture Class---------------------------------------------
//
class TimerTest: public ::testing::Test
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
TEST_F(TimerTest, SimpleUseOfTimer)
{
    steady_clock::time_point t0;
    steady_clock::time_point t1 = t0 + milliseconds(10);
    steady_clock::time_point t2 = t0 + milliseconds(50);
    steady_clock::time_point t3 = t0 + milliseconds(100);

    MockRepository stdClock;
    stdClock.ExpectCallFunc(steady_clock::now).Return(t0);
    stdClock.ExpectCallFunc(steady_clock::now).Return(t1);
    stdClock.ExpectCallFunc(steady_clock::now).Return(t2);
    stdClock.ExpectCallFunc(steady_clock::now).Return(t3);

    Timer timer;
    timer.start();
    timer.restart();

    EXPECT_EQ(50, timer.ellapsed());
}
