HOSTCC=g++
RASPCC=arm-linux-gnueabihf-g++

GTEST_DIR=../../../../CotsCode/googletest
HOST_GTEST_DIR=${GTEST_DIR}/host/googletest

CFLAGS=-Wall -std=c++11
LIBS=-L${HOST_GTEST_DIR} -lgtest -lgtest_main -lpthread
INCL=-I$(GTEST_DIR)/googletest/include -I../..

TARGET=unit_test

SOURCES = EventTest.cpp
	  #../../Event.cpp \
../../Listener.cpp \

OBJECTS=$(SOURCES:.cpp=.o)


.PHONY: default all clean

default: $(TARGET)
all: default

.cpp.o:
	$(HOSTCC) $(CFLAGS) $(INCL) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	-mkdir -p bin
	$(HOSTCC) $(CFLAGS) $(OBJECTS) $(INCL) $(LIBS) -o bin/$@

clean:
	-rm -f $(OBJECTS)
	-rm -rf bin
