# ----- COMMON CONSTANTS ----------------------------------------------------- 

APP_NAME=ClientLoopBackTest
PRJ_ROOT=../../../..

include ${PRJ_ROOT}/make_rules/base.mak
include ${PRJ_ROOT}/make_rules/host.mak
include ${PRJ_ROOT}/make_rules/rasp.mak

CFLAGS=-Wall -std=c++11
INCL=-I$(PRJ_ROOT)/common -I../../..
LIBS=

SOURCES = main.cpp \
	  ../../../TCPClient.cpp

BINDIR=bin


.PHONY: default all clean kcov rasp host
HOST_TARGET=host_clientloopback
RASP_TARGET=rasp_clientloopback

default: $(BINDIR) $(HOST_TARGET)
host: default
rasp: $(BINDIR) $(RASP_TARGET)
all: rasp default


# ----- HOST TARGET ---------------------------------------------------------- 
HOST_LIBS=$(LIBS)
HOST_INCL=$(INCL)
HOST_OBJECTS=$(SOURCES:.cpp=.ho)

%.ho: %.cpp
	$(HOSTCC) $(CFLAGS) $(HOST_INCL) -D APP_NAME=$(APP_NAME) -c $< -o $@


$(HOST_TARGET): $(HOST_OBJECTS)
	$(HOSTCC) $(CFLAGS) $(HOST_OBJECTS) $(HOST_INCL) $(HOST_LIBS) -o $(BINDIR)/$@




# ----- RASPBERRY TARGET ----------------------------------------------------- 
RASP_LIBS=$(LIBS)
RASP_INCL=$(INCL)
RASP_OBJECTS=$(SOURCES:.cpp=.ro)


%.ro: %.cpp
	$(RASPCC) $(CFLAGS) $(RASP_INCL) -D APP_NAME=$(APP_NAME) -c $< -o $@

$(RASP_TARGET): $(RASP_OBJECTS)
	$(RASPCC) $(CFLAGS) $(RASP_OBJECTS) $(RASP_INCL) $(RASP_LIBS) -o $(BINDIR)/$@



# ----- OTHER TARGETS -------------------------------------------------------- 
.PRECIOUS: $(HOST_TARGET) $(RASP_TARGET) $(HOST_OBJECTS) $(RASP_OBJECTS)

clean:
	-rm -f $(HOST_OBJECTS) $(RASP_OBJECTS)
	-rm -rf $(BINDIR) $(KCOV_OUTDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
