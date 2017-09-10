#include <string>
#include <functional>
#include "gtest/gtest.h"
#include "Event.h"

using namespace std::placeholders;

class IntListener
{
    public:

        IntListener(){}
        IntListener(int val): val(val){}
        ~IntListener(){}

        void setVal(int i){this->val = i;}

        int val;
};

class IntArrayListener
{
    public:
        IntArrayListener(){}
        IntArrayListener(std::vector<int> val): val(val){}
        ~IntArrayListener(){}

        void setVal(std::vector<int> vec){val = vec;}

        std::vector<int> val;
};

class StringListener
{
    public:
        StringListener(){}
        StringListener(std::string val): val(val){}
        ~StringListener(){}

        void setVal(std::string s){val = s;}

        std::string val;
};

// Unit Test Fixture Class---------------------------------------------
//
class EventTest: public ::testing::Test
{
    protected:

        // Events
        Event<int> evInt1;
        Event<int> evInt2;
        Event<std::vector<int> > evArray1;
        Event<std::vector<int> > evArray2;
        Event<std::string> evStr1;
        Event<std::string> evStr2;

        // Listeners
        IntListener iListA;
        IntListener iListB;
        IntListener iListC;
        IntArrayListener aListA;
        IntArrayListener aListB;
        IntArrayListener aListC;
        StringListener sListA;
        StringListener sListB;
        StringListener sListC;

        virtual void SetUp() 
        {
            // Integer listeners
            iListA = IntListener(0);
            iListB = IntListener(0);
            iListC = IntListener(0);

            // Integer array listeners
            std::vector<int> array {0,0,0,0,0};
            aListA = IntArrayListener(array);
            aListB = IntArrayListener(array);
            aListC = IntArrayListener(array);

            // String listeners
            sListA = StringListener("");
            sListB = StringListener("");
            sListC = StringListener("");
        }

        virtual void TearDown()
        {
        }
};


// Test Cases ---------------------------------------------------------
//
TEST_F(EventTest, MultipleCallbacksFromDifferentTypes)
{
    const std::vector<int> arr1 = {0,0,0,0,0};
    const std::vector<int> arr2 = {1,2,3,4,5};
    const std::vector<int> arr3 = {5,4,3,2,1};

    // Connect listeners with events
    evInt1.subscribe(std::bind(&IntListener::setVal, &iListA, _1));
    evInt1.subscribe(std::bind(&IntListener::setVal, &iListB, _1));
    evInt2.subscribe(std::bind(&IntListener::setVal, &iListC, _1));

    evArray1.subscribe(std::bind(&IntArrayListener::setVal, &aListA, _1));
    evArray1.subscribe(std::bind(&IntArrayListener::setVal, &aListB, _1));
    evArray2.subscribe(std::bind(&IntArrayListener::setVal, &aListC, _1));

    evStr1.subscribe(std::bind(&StringListener::setVal, &sListA, _1));
    evStr2.subscribe(std::bind(&StringListener::setVal, &sListB, _1));
    evStr2.subscribe(std::bind(&StringListener::setVal, &sListC, _1));

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

    // Check object values againg. They should've changed
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
    evInt1.subscribe(std::bind(&IntListener::setVal, &iListA, _1));
    evInt1.subscribe(std::bind(&IntListener::setVal, &iListB, _1));

    evInt1.emit(100);

    // Both listeners should've received the event
    EXPECT_EQ(100, iListA.val);
    EXPECT_EQ(100, iListB.val);

    // Now disconnect Listener A
    //evInt1.remove(std::bind(&IntListener::setVal, &iListA, _1));

    evInt1.emit(17);

    // I hope that now that only Listener B will receive this
    EXPECT_EQ(100, iListA.val);
    EXPECT_EQ(17, iListB.val);
}

TEST_F(EventTest, TryToExecuteCallbackFromObjectWichNoLogerExists)
{
}

TEST_F(EventTest, TryToSubscribeCallbackTwoTimesInARow)
{
}

TEST_F(EventTest, TryToRemoveCallbackTwoTimesInARow)
{
}

