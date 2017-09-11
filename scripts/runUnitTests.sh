#!/bin/bash

# DESCRIPTION: 
#       This script runs the unit tests provided by the config file
#       'UnitTests.txt'. This config file is just a list of paths
#       to where the directories 'test' are located. The unit tests
#       are aways executed with the --gtest_shuffle flag ON which
#       executes the test cases in a random order.
#
# USAGE:
#       ./runUnitTests.sh [option] [-n NUMBER]
#
#           Options:
#               [--host]        Run unit tests on host machine
#               [--rasp]        Run unit test on Raspberry Pi. Remember
#                               check the default IP address of the hardware
#               [-n NUMBER]     Run unit tests NUMBER times (Ex. -n 500 will
#                               run the tests 500 times in a row). Default
#                               value is 1.
#               [--help | -h]   Print a help message


# Include constants and functions
source utils.sh

print_help() {
    printf "${GRAY}"
    printf "USAGE: ./runUnitTests.sh [option] -n[NUMBER]\n\n"
    printf "Options:\n"
    printf "\t[--host]\tRun unit tests on host machine\n"
    printf "\t[--rasp]\tRun unit test on Raspberry Pi. Remember\n"
    printf "\t\t\tcheck the default IP address of the hardware\n"
    printf "\t[-n NUMBER]\tRun unit tests NUMBER times (Ex. -n 500 will\n"
    printf "\t\t\trun the tests 500 times in a row). Default\n\t\t\tvalue is 1\n"
    printf "\t[--help | -h]\tPrint this help message\n"
    printf "${NC}"
}


machineName=
bin=
repeat=1
configFile="UnitTests.txt"
while test $# -gt 0; do
    case $1 in
        --host)
            machineName="Host Machine"
            bin=host_unit
            shift
            ;;
        --rasp)
            machineName="Raspberry Pi"
            bin=rasp_unit
            shift
            ;;
        -n*)
            shift
            if test $# -gt 0; then
                repeat=$1
            else
                printf "${RED}No NUMBER specified!${NC}\n"
            fi
            shift
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
done


if [ "$bin" == "" ]; then
    printf "${RED}No machine specified. Use one of the arguments: --rasp / --host${NC}\n"
    print_help
    exit 1
fi

# Parse config file
while IFS='' read -r path || [[ -n "$path"  ]]; do

    pushd "${path}/test/unit"

    printf "${YELLOW}* Running unit test from ${path}${NC}\n"
    sleep 3

    if [ ! -d bin ]; then
        printf "${BLUE}Binaries not found. Trying to build${NC}\n"
        make all || exit 1
    fi

    pushd bin

    cmd=
    logout=
    if [ "${bin}" == "rasp_unit" ]; then
        scp bin/${bin} pi@${rpiIp}:/home/pi
        cmd="ssh pi@${rpiIp}"
        logout=exit
    fi

    cmd="${cmd} ./${bin} --gtest_repeat=${repeat} --gtest_shuffle"

    # Run test
    ${cmd}

    popd
    popd

done < "${configFile}"
