#!/bin/bash

# DESCRIPTION: 
#       This script build the Cots code downloaded. You can build it
#       for your host system (e.g. to run unit tests in the host) or
#       cross compile for the raspberry in order to run the application
#       or run the tests in the hardware.
#
# USAGE:
#       ./buildCotsCode.sh [option]
#
#           Options:
#               [--host]        Build Cots for host system
#               [--rasp]        Cross compile for raspberry using toolchain
#               [--help | -h]   Print a help message


# Include constants and functions
source utils.sh

print_help() {
    printf "${GRAY}"
    printf "USAGE: ./buildCotsCode.sh [option]\n\n"
    printf "Options:\n"
    printf "\t[--host]\tBuild Cots for host system\n"
    printf "\t[--rasp]\tCross compile for raspberry using toolchain\n"
    printf "\t[--help | -h]\tPrint this help message\n"
    printf "${NC}"
}


machineName=
binDir=
cmakeToolOption=
case $1 in
    --host)
        machineName="Host Machine"
        binDir=host
        cmakeToolOption=
        ;;
    --rasp)
        machineName="Raspberry Pi"
        binDir=rasp
        cmakeToolOption="-DCMAKE_TOOLCHAIN_FILE=../../../scripts/toolchain-arm-linux.cmake"
        ;;
    -h|--help)
        print_help
        exit 0
        ;;
    ""|" ")
        printf "${RED}This script needs an argument${NC}\n"
        print_help
        exit 1
        ;;
    *)
        printf "${RED}Argument $1 is not valid${NC}\n"
        print_help
        exit 1
        ;;
esac


pushd ..
pushd CotsCode

printf "\n\n${LBLUE}----- Building dependecies for $machineName -----\n"


for ((i = 0; i < ${#repos[@]}; ++i)); do

    printf "\n${GREEN}* Building ${repos[$i]}: ${description[$i]}"
    printf "${NC}\n"
    sleep 3

    pushd ${repos[$i]}
    mkdir -p $binDir
    pushd $binDir

    cmake ${cmakeFlags[$i]} $cmakeToolOption ..
    make -j5

    popd
    popd

done


printf "${NC}\n\n"
popd
popd

exit 0
