# ----- COMMON CONSTANTS ----------------------------------------------------- 

APP_NAME=CommonTestApp
PRJ_ROOT=../../../..

include ${PRJ_ROOT}/make_rules/base.mak
include ${PRJ_ROOT}/make_rules/host.mak
include ${PRJ_ROOT}/make_rules/rasp.mak

CFLAGS=-Wall -std=c++11
INCL=-I$(GTEST_INC) -I$(HIPPOMOCKS_INC) -I../..
LIBS=$(GTEST_LIBS)

SOURCES = EventTest.cpp \
	  LogTest.cpp \
	  TimerTest.cpp \
	  ../../Timer.cpp

BINDIR=bin


.PHONY: default all clean kcov rasp host
HOST_TARGET=host_unit
RASP_TARGET=rasp_unit

default: $(BINDIR) $(HOST_TARGET)
host: default
rasp: $(BINDIR) $(RASP_TARGET)
all: rasp default


# ----- HOST TARGET ---------------------------------------------------------- 
HOST_LIBS=-L${HOST_GTEST_DIR} ${LIBS}
HOST_OBJECTS=$(SOURCES:.cpp=.ho)

%.ho: %.cpp
	$(HOSTCC) $(CFLAGS) $(INCL) -D APP_NAME=$(APP_NAME) -c $< -o $@


$(HOST_TARGET): $(HOST_OBJECTS)
	$(HOSTCC) $(CFLAGS) $(HOST_OBJECTS) $(INCL) $(HOST_LIBS) -o $(BINDIR)/$@




# ----- RASPBERRY TARGET ----------------------------------------------------- 
RASP_LIBS=-L${RASP_GTEST_DIR} $(LIBS)
RASP_OBJECTS=$(SOURCES:.cpp=.ro)


%.ro: %.cpp
	$(RASPCC) $(CFLAGS) $(INCL) -D APP_NAME=$(APP_NAME) -c $< -o $@

$(RASP_TARGET): $(RASP_OBJECTS)
	$(RASPCC) $(CFLAGS) $(RASP_OBJECTS) $(INCL) $(RASP_LIBS) -o $(BINDIR)/$@



# ----- OTHER TARGETS -------------------------------------------------------- 
.PRECIOUS: $(HOST_TARGET) $(RASP_TARGET) $(HOST_OBJECTS) $(RASP_OBJECTS)

KCOV_OUTDIR=kcov
KCOV_FLAGS=--include-path=../..

kcov: $(HOST_TARGET)
	-$(KCOV) $(KCOV_FLAGS) $(KCOV_OUTDIR) $(BINDIR)/$(HOST_TARGET)

clean:
	-rm -f $(HOST_OBJECTS) $(RASP_OBJECTS)
	-rm -rf $(BINDIR) $(KCOV_OUTDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
