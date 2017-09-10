


# ----- COMMON CONSTANTS ----------------------------------------------------- 
GTEST_DIR=../../../../CotsCode/googletest

CFLAGS=-Wall -std=c++11
INCL=-I$(GTEST_DIR)/googletest/include -I../..
LIBS=-lgtest -lgtest_main -lpthread

SOURCES = EventTest.cpp

BINDIR=bin


.PHONY: default all clean kcov rasp host
HOST_TARGET=host_unit
RASP_TARGET=rasp_unit

rasp: $(BINDIR) $(RASP_TARGET)
default: $(BINDIR) $(HOST_TARGET)
all: rasp default
host: default


# ----- HOST TARGET ---------------------------------------------------------- 
HOSTCC=g++
HOST_GTEST_DIR=${GTEST_DIR}/host/googletest
HOST_LIBS=-L${HOST_GTEST_DIR} $(LIBS)
HOST_OBJECTS=$(SOURCES:.cpp=.ho)

%.ho: %.cpp
	$(HOSTCC) $(CFLAGS) $(INCL) -c $< -o $@


$(HOST_TARGET): $(HOST_OBJECTS)
	$(HOSTCC) $(CFLAGS) $(HOST_OBJECTS) $(INCL) $(HOST_LIBS) -o $(BINDIR)/$@




# ----- RASPBERRY TARGET ----------------------------------------------------- 
RASPCC=arm-linux-gnueabihf-g++
RASP_GTEST_DIR=${GTEST_DIR}/rasp/googletest
RASP_LIBS=-L${RASP_GTEST_DIR} $(LIBS)
RASP_OBJECTS=$(SOURCES:.cpp=.ro)


%.ro: %.cpp
	$(RASPCC) $(CFLAGS) $(INCL) -c $< -o $@

$(RASP_TARGET): $(RASP_OBJECTS)
	$(RASPCC) $(CFLAGS) $(RASP_OBJECTS) $(INCL) $(RASP_LIBS) -o $(BINDIR)/$@



# ----- OTHER TARGETS -------------------------------------------------------- 
.PRECIOUS: $(HOST_TARGET) $(RASP_TARGET) $(HOST_OBJECTS) $(RASP_OBJECTS)

KCOV=../../../../CotsCode/kcov/host/src/kcov 
KCOV_OUTDIR=kcov
KCOV_FLAGS=--include-path=../..

kcov: $(HOST_TARGET)
	-$(KCOV) $(KCOV_FLAGS) $(KCOV_OUTDIR) $(BINDIR)/$(HOST_TARGET)

clean:
	-rm -f $(HOST_OBJECTS) $(RASP_OBJECTS)
	-rm -rf $(BINDIR) $(KCOV_OUTDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
