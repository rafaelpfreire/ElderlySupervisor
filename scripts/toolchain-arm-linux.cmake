# DESCRIPTION:
#       This file is used for cmake to cross-compile the Cots Code for
#       raspberry pi.


# target system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# cross compiler
SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH /usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Googletest cannot use TRY_RUN() when cross compiling
# setting this variable to omit a TRY_RUN() error
SET( THREADS_PTHREAD_ARG 
     "PLEASE_FILL_OUT-FAILED_TO_RUN"
     CACHE STRING "Result from TRY_RUN" FORCE)
