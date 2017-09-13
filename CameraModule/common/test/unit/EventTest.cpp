#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "Event.h"
#include "Handler.h"

using namespace std::placeholders;

class IntListener
{
    public:

        IntListener(int val = 0): val(val)
        {
            intHandler.reset(new Handler<int>(std::bind(&IntListener::setVal, this, _1)));
        }
        ~IntListener(){}

        void setVal(int i){val = i;}

        int val;
        std::shared_ptr<Handler<int>> intHandler;
};

class IntArrayListener
{
    using IntArrayHandler = Handler<std::vector<int> >;
    using IntArrayHandlerPtr = std::shared_ptr<IntArrayHandler>;

    public:
        IntArrayListener(std::vector<int> val = {}): val(val)
        {
            aHandler.reset(new IntArrayHandler(std::bind(&IntArrayListener::setVal, this, _1)));
        }
        ~IntArrayListener(){}

        void setVal(std::vector<int> vec){val = vec;}

        std::vector<int> val;
        IntArrayHandlerPtr aHandler;
};

class StringListener
{
    using StringHandler = Handler<std::string>;
    using StringHandlerPtr = std::shared_ptr<StringHandler>;

    public:
        StringListener(std::string val = ""): val(val)
        {
            strHandler.reset(new StringHandler(std::bind(&StringListener::setVal, this, _1)));
        }
        ~StringListener(){}

        void setVal(std::string s){val = s;}

        std::string val;
        StringHandlerPtr strHandler;
};

// Unit Test Fixture Class---------------------------------------------
//
class EventTest: public ::testing::Test
{
    protected:

        const std::vector<int> arr1 = {0,0,0,0,0};
        const std::vector<int> arr2 = {1,2,3,4,5};
        const std::vector<int> arr3 = {5,4,3,2,1};

        virtual void SetUp() 
        {
        }

        virtual void TearDown()
        {
        }
};


// Test Cases ---------------------------------------------------------
//
TEST_F(EventTest, MultipleCallbacksFromDifferentTypes)
{
    // Events
    Event<int> evInt1;
    Event<int> evInt2;
    Event<std::vector<int> > evArray1;
    Event<std::vector<int> > evArray2;
    Event<std::string> evStr1;
    Event<std::string> evStr2;

    // Listeners
    IntListener iListA(0);
    IntListener iListB(0);
    IntListener iListC(0);
    IntArrayListener aListA(arr1);
    IntArrayListener aListB(arr1);
    IntArrayListener aListC(arr1);
    StringListener sListA("");
    StringListener sListB("");
    StringListener sListC("");

    // Connect listeners with events
    evInt1.subscribe(iListA.intHandler);
    evInt1.subscribe(iListB.intHandler);
    evInt2.subscribe(iListC.intHandler);
    evArray1.subscribe(aListA.aHandler);
    evArray1.subscribe(aListB.aHandler);
    evArray2.subscribe(aListC.aHandler);
    evStr1.subscribe(sListA.strHandler);
    evStr2.subscribe(sListB.strHandler);
    evStr2.subscribe(sListC.strHandler);

    // Check object values before emiting events
    EXPECT_EQ(0, iListA.val);
    EXPECT_EQ(0, iListB.val);
    EXPECT_EQ(0, iListC.val);
    EXPECT_EQ(arr1, aListA.val);
    EXPECT_EQ(arr1, aListB.val);
    EXPECT_EQ(arr1, aListC.val);
    EXPECT_STREQ("", sListA.val.c_str());
    EXPECT_STREQ("", sListB.val.c_str());
    EXPECT_STREQ("", sListC.val.c_str());

    // Emit events
    evInt1.emit(42);
    evInt2.emit(51);
    evArray1.emit(arr2);
    evArray2.emit(arr3);
    evStr1.emit("Testing Event");
    evStr2.emit("Uhuuuuu");

    // Check object values again. They should've changed
    EXPECT_EQ(42, iListA.val);
    EXPECT_EQ(42, iListB.val);
    EXPECT_EQ(51, iListC.val);
    EXPECT_EQ(arr2, aListA.val);
    EXPECT_EQ(arr2, aListB.val);
    EXPECT_EQ(arr3, aListC.val);
    EXPECT_STREQ("Testing Event", sListA.val.c_str());
    EXPECT_STREQ("Uhuuuuu", sListB.val.c_str());
    EXPECT_STREQ("Uhuuuuu", sListC.val.c_str());
}


TEST_F(EventTest, RemovingCallbackFromEvent)
{
    Event<int> evInt1;
    IntListener iListA(0);
    IntListener iListB(0);

    evInt1.subscribe(iListA.intHandler);
    evInt1.subscribe(iListB.intHandler);

    evInt1.emit(100);

    // Both listeners should've received the event
    EXPECT_EQ(100, iListA.val);
    EXPECT_EQ(100, iListB.val);

    // Now disconnect Listener A
    evInt1.remove(iListA.intHandler);

    evInt1.emit(17);

    // I hope that now only Listener B will receive this event
    EXPECT_EQ(100, iListA.val);
    EXPECT_EQ(17, iListB.val);
}


// !!! NEVER DO THIS: BUG. FIX IN THE FUTURE
//
//TEST_F(EventTest, TryToExecuteCallbackFromObjectWichNoLogerExists)
//{
//    Event<int> evInt1;
//    std::shared_ptr<IntListener> ptr;
//    ptr.reset(new IntListener(0));
//
//    evInt1.subscribe(ptr->intHandler);
//
//    evInt1.emit(10);
//
//    ptr.reset();
//
//    evInt1.emit(11);
//    ASSERT_TRUE(true);
//}


TEST_F(EventTest, TryToSubscribeCallbackTwoTimesInARow)
{
    Event<int> evInt1;
    IntListener iListA(0);

    evInt1.subscribe(iListA.intHandler);
    evInt1.subscribe(iListA.intHandler);

    evInt1.emit(10);
    ASSERT_TRUE(true);
}

TEST_F(EventTest, TryToRemoveCallbackTwoTimesInARow)
{
    Event<int> evInt1;
    IntListener iListA(0);

    evInt1.subscribe(iListA.intHandler);
    evInt1.remove(iListA.intHandler);
    evInt1.remove(iListA.intHandler);

    evInt1.emit(10);
    ASSERT_TRUE(true);
}
