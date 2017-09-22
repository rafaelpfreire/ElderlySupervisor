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
    "opencv"
#    "curl"
)
url=(
    "https://github.com/google/googletest"
    "https://github.com/SimonKagstrom/kcov"
    "https://github.com/dascandy/hippomocks"
    "https://github.com/openssl/openssl"
    "https://github.com/libssh2/libssh2"
    "https://github.com/opencv/opencv"
#    "https://github.com/curl/curl"
)
description=(
    "unit test framework"
    "code coverage analysis for unit tests"
    "mocking framework for unit tests"
    "toolkit implementing the Transport Layer Security (TLS) protocols"
    "library implementing the SSH2 protocol"
    "open source computer vision library"
#    "network data transfer library wich supports a lot of protocols"
)

buildType=(
    "cmake"
    "cmake"
    "cmake"
    "script"
    "cmake"
    "cmake"
)

# CMake flags
get_cmake_flags() {

    idx=$1
    trg=$2

    sslRootDir=../../openssl/${trg}
    ocvRootDir=../../opencv/${trg}

    gtkflag=
    if [ "$trg" == "rasp" ]; then
        gtkflag=OFF
    else
        gtkflag=ON
    fi

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
        "-DCMAKE_BUILD_TYPE=RELEASE \
            -DCMAKE_INSTALL_PREFIX=${ocvRootDir} \
            -DBUILD_EXAMPLES=OFF \
            -DBUILD_DOCS=OFF \
            -DBUILD_PERF_TESTS=OFF \
            -DBUILD_TESTS=OFF \
            -DWITH_TBB=ON -DBUILD_TBB=ON \
            -DWITH_V4L=ON -DWITH_OPENGL=ON \
            -DWITH_OPENMP=ON -DWITH_IPP=ON \
            -DWITH_NVCUVID=ON -DWITH_CUDA=ON \
            -DWITH_CSTRIPES=ON -DWITH_OPENCL=ON \
            -DWITH_GTK=${gtkflag}"
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
