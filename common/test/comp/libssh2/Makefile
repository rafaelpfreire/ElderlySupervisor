# ----- COMMON CONSTANTS ----------------------------------------------------- 

APP_NAME=LibSSH2ComponentTest
PRJ_ROOT=../../../..

include ${PRJ_ROOT}/make_rules/base.mak
include ${PRJ_ROOT}/make_rules/host.mak

CFLAGS=-Wall -std=c++11
INCL=-I$(HOST_SSH2_DIR) -I$(SSH2_INC) -I../../..
LIBS=-L$(HOST_GTEST_DIR) -L$(HOST_OPENSSL_DIR) -L$(HOST_SSH2_DIR) $(SSH2_LIBS) $(OPENSSL_LIBS) 

SOURCES = LibSSH2FacadeCompTest.cpp \
	  ../../../LibSSH2Facade.cpp

BINDIR=bin


.PHONY: default all clean
TARGET=scp

default: $(BINDIR) $(TARGET)
all: default


# ----- HOST TARGET ---------------------------------------------------------- 
OBJECTS=$(SOURCES:.cpp=.ho)

%.ho: %.cpp
	$(HOSTCC) $(CFLAGS) $(INCL) -D APP_NAME=$(APP_NAME) -c $< -o $@


$(TARGET): $(OBJECTS)
	$(HOSTCC) $(CFLAGS) $(OBJECTS) $(INCL) $(LIBS) -o $(BINDIR)/$@



# ----- OTHER TARGETS -------------------------------------------------------- 
.PRECIOUS: $(TARGET) $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -rf $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
