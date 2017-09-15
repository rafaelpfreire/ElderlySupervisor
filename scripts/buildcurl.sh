



printf "Running $0 script"
#binDir=
#case $1 in
#    --host)
#        binDir=host
#        ;;
#    --rasp)
#        binDir=rasp
#        ;;
#    -h|--help)
#        print_help
#        exit 0
#        ;;
#    ""|" ")
#        printf "${RED}This script needs an argument${NC}\n"
#        print_help
#        exit 1
#        ;;
#    *)
#        printf "${RED}Argument $1 is not valid${NC}\n"
#        print_help
#        exit 1
#        ;;
#esac
#
#
#./buildconf
#
#compiler=
#if [ "$binDir" == "rasp" ]; then
#    compiler=arm-linux-gnueabihf-gcc
#else
#    compiler=gcc
#fi
#
#CC=$compiler ./configure --host=arm-linux-gnueabihf --prefix=$(pwd)/$binDir --enable-debug --without-zlib --with-libssh2=PATH --with-ssl=PATH 
