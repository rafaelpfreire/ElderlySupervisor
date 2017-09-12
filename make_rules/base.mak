# ----- COMMON MAKEFILE CONSTANTS  ------------------------------------------- 

COTS_DIR=${PRJ_ROOT}/CotsCode

GTEST_DIR=${COTS_DIR}/googletest
GTEST_INC=${GTEST_DIR}/googletest/include
GTEST_LIBS=-lgtest -lgtest_main -lpthread

HIPPOMOCKS_DIR=${COTS_DIR}/hippomocks
HIPPOMOCKS_INC=${HIPPOMOCKS_DIR}/HippoMocks

KCOV=${KCOV_DIR}/host/src/kcov 
KCOV_DIR=${COTS_DIR}/kcov
