#!/bin/bash

# DESCRIPTION: 
#       Utilities package to simplify the other scripts
#
# USAGE:
#       This script is not intended to be used alone. It is intended
#       to be used by other scripts


# ANSI escape color codes (NC: no color)
RED='\033[0;31m'
BLUE='\033[0;34m'
LBLUE='\033[1;34m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
GRAY='\033[1;30m'
NC='\033[1;0m'


# Rpi default ip address (/etc/hosts)
rpiIp=pia

# Constants
repos=(
    "googletest"
    "kcov"
    "hippomocks"
    "openssl"
    "libssh2"
#    "curl"
#    "opencv"
)
url=(
    "https://github.com/google/googletest"
    "https://github.com/SimonKagstrom/kcov"
    "https://github.com/dascandy/hippomocks"
    "https://github.com/openssl/openssl"
    "https://github.com/libssh2/libssh2"
#    "https://github.com/curl/curl"
#    "https://github.com/opencv/opencv"
)
description=(
    "unit test framework"
    "code coverage analysis for unit tests"
    "mocking framework for unit tests"
    "toolkit implementing the Transport Layer Security (TLS) protocols"
    "library implementing the SSH2 protocol"
#    "network data transfer library wich supports a lot of protocols"
#    "open source computer vision library"
)

#cmake -DCMAKE_TOOLCHAIN_FILE=../../../scripts/toolchain-arm-linux.cmake -DCRYPTO_BACKEND=OpenSSL -DOPENSSL_ROOT_DIR=../../openssl/rasp -DOPENSSL_LIBRARIES=../../openssl/rasp/lib -DOPENSSL_CRYPTO_LIBRARY=../../openssl/rasp/lib/libcrypto.so.1.1 -DOPENSSL_SSL_LIBRARY=../../openssl/rasp/lib/libssl.so.1.1 -DOPENSSL_INCLUDE_DIR=../../openssl/rasp/include -DBUILD_EXAMPLES=OFF -DBUILD_TESTING=OFF -DBUILD_SHARED_LIBS=ON -DENABLE_DEBUG_LOGGING=ON ../

buildType=(
    "cmake"
    "cmake"
    "cmake"
    "script"
    "cmake"
#    ""
#    ""
)


# CMake flags
get_cmake_flags () {

    idx=$1
    trg=$2

    sslRootDir=../../openssl/${trg}

    cmakeFlags=(
        "-DBUILD_GTEST=ON -DBUILD_GMOCK=OFF"
        ""
        ""
        ""
        "-DCRYPTO_BACKEND=OpenSSL \
            -DOPENSSL_ROOT_DIR=${sslRootDir} \
            -DOPENSSL_LIBRARIES=${sslRootDir}/lib \
            -DOPENSSL_CRYPTO_LIBRARY=${sslRootDir}/lib/libcrypto.so \
            -DOPENSSL_SSL_LIBRARY=${sslRootDir}/lib/libssl.so \
            -DOPENSSL_INCLUDE_DIR=${sslRootDir}/include \
            -DBUILD_EXAMPLES=OFF -DBUILD_TESTING=OFF \
            -DBUILD_SHARED_LIBS=ON -DENABLE_DEBUG_LOGGING=ON"
    #    ""
    #    ""
    )

    echo ${cmakeFlags[$idx]}
}

# Do not display pushd and popd outputs on the command line
pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}
