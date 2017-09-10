#!/bin/bash

# DESCRIPTION: 
#       This script downloads the necessary Cots code in order to
#       build the application and tests.
#
# USAGE:
#       ./getCotsCode.sh


# Include constants and functions
source utils.sh


pushd ..
mkdir -p CotsCode
pushd CotsCode

printf "\n\n${LBLUE}----- Cloning github repos -----\n"

for ((i = 0; i < ${#repos[@]}; ++i)); do

    printf "\n${GREEN}* Cloning ${repos[$i]}: ${description[$i]}"
    printf "${GRAY}\n"
    git clone ${url[$i]} ${repos[$i]}

done

printf "${NC}\n\n"
popd
popd

exit 0
