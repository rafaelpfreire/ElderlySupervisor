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

OPENCV_DIR=${COTS_DIR}/opencv
OPENCV_LIBS=-lopencv_calib3d -lopencv_core -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videoio -lopencv_video -lopencv_videostab
