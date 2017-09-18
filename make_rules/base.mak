# ----- COMMON MAKEFILE CONSTANTS  ------------------------------------------- 

COTS_DIR=${PRJ_ROOT}/CotsCode

GTEST_DIR=${COTS_DIR}/googletest
GTEST_INC=${GTEST_DIR}/googletest/include
GTEST_LIBS=-lgtest -lgtest_main -lpthread

HIPPOMOCKS_DIR=${COTS_DIR}/hippomocks
HIPPOMOCKS_INC=${HIPPOMOCKS_DIR}/HippoMocks

KCOV=${KCOV_DIR}/host/src/kcov 
KCOV_DIR=${COTS_DIR}/kcov

OPENSSL_DIR=${COTS_DIR}/openssl
OPENSSL_INC=${OPENSSL_DIR}/include
OPENSSL_LIBS=-lcrypto -lssl

SSH2_DIR=${COTS_DIR}/libssh2
SSH2_INC=${SSH2_DIR}/include
SSH2_LIBS=-lssh2
