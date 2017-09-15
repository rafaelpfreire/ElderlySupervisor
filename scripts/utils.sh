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

# Constants
repos=(
    "googletest"
    "kcov"
    "hippomocks"
    "openssl"
#    "libssh2"
#    "curl"
#    "opencv"
)
url=(
    "https://github.com/google/googletest"
    "https://github.com/SimonKagstrom/kcov"
    "https://github.com/dascandy/hippomocks"
    "https://github.com/openssl/openssl"
#    "https://github.com/libssh2/libssh2"
#    "https://github.com/curl/curl"
#    "https://github.com/opencv/opencv"
)
description=(
    "unit test framework"
    "code coverage analysis for unit tests"
    "mocking framework for unit tests"
    "toolkit implementing the Transport Layer Security (TLS) protocols"
#    "library implementing the SSH2 protocol"
#    "network data transfer library wich supports a lot of protocols"
#    "open source computer vision library"
)
cmakeFlags=(
    "-DBUILD_GTEST=ON -DBUILD_GMOCK=OFF"
    ""
    ""
    ""
#    ""
#    ""
#    ""
)
buildType=(
    "cmake"
    "cmake"
    "cmake"
    "script"
#    ""
#    ""
#    ""
)

# Rpi default ip address (/etc/hosts)
rpiIp=pia

# Do not display pushd and popd outputs on the command line
pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}
