

target=
case $1 in
    --host)
        target=host
        ;;
    --rasp)
        target=rasp
        ;;
    -h|--help)
        print_help
        exit 0
        ;;
    ""|" ")
        printf "${RED}This script needs an argument${NC}\n"
        exit 1
        ;;
    *)
        printf "${RED}Argument $1 is not valid${NC}\n"
        exit 1
        ;;
esac


# Configure script for host or rasp
if [ "${target}" == "host" ]; then

    ./config -DOPENSSL_NO_HEARTBEATS \
             --prefix=$(pwd)/${target} \
             --openssldir=$(pwd)/${target} \
             -Wl,-rpath,$(pwd)/${target}/lib

    # Check if there is the need to build or clean up
    if [ -f host/bin/openssl ]; then
        printf "No need to build openssl for host\n"
        exit 0
    elif [ -f rasp/bin/openssl ]; then
        make clean
    fi

else

    CROSS=arm-linux-gnueabihf
    CROSS_COMPILE=${CROSS}- ./Configure linux-armv4 \
                                    -DOPENSSL_NO_HEARTBEATS \
                                    --prefix=$(pwd)/${target} \
                                    --openssldir=$(pwd)/${target} shared 

    # Check if there is the need to build or clean up
    if [ -f rasp/bin/openssl ]; then
        printf "No need to build openssl for Raspberry Pi\n"
        exit 0
    elif [ -f host/bin/openssl ]; then
        make clean
    fi

fi

# Build library
make
make install

exit 0
