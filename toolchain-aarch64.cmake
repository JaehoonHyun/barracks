############################      HOW TO USE       ##################################
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-aarch64.cmake -DCMAKE_TARGET=SHARED  #
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-aarch64.cmake -DCMAKE_TARGET=STATIC  #
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-aarch64.cmake -DCMAKE_TARGET=EXECUTE #
#####################################################################################

###############
# SYSTEM INFO #
###############
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_NAME      "Linux")
SET(CMAKE_SYSTEM_PROCESSOR "aarch64")


#######################
# CROSS COMPILER INFO #
#######################
SET(CMAKE_C_COMPILER         "/usr/bin/aarch64-linux-gnu-gcc-4.9")
SET(CMAKE_CXX_COMPILER       "/usr/bin/aarch64-linux-gnu-g++-4.9")
SET(CMAKE_CPP_COMPILER       "/usr/bin/aarch64-linux-gnu-cpp-4.9")
SET(CMAKE_C_COMPILER_AR      "/usr/bin/aarch64-linux-gnu-gcc-ar-4.9")
SET(CMAKE_C_COMPILER_RANLIB  "/usr/bin/aarch64-linux-gnu-gcc-ranlib")

###########################
# External Library Header #
###########################
SET(EXT_LIB_HEADER /usr/local/aarch64/include
                   /usr/local/aarch64/sdk/native/jni/include)

#############################
# External Library Location #
#############################
SET (EXTERNAL_LINK_LIB  /usr/local/aarch64/lib/libzmq.so
                        /usr/local/aarch64/lib/libpistache.so
                        /usr/local/aarch64/lib/libopencv_core.so.3.4.2
                        # /usr/local/aarch64/lib/libtensorflowLite.so
                        # /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_core.so.3.4.2
                        # /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_highgui.so
                        # /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_xfeatures2d.so
                        # /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_flann.so
                        # /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_imgcodecs.so
                        # /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_imgproc.so 
                        )


#############################
# Standard Library Location #
#############################
#SET (STANDARD_LINK_LIB  log 
#                        gnustl_shared)

########
# link #
########
SET(MY_LINK_DIRECTORIES  "-L/usr/local/aarch64 -L/usr/local/aarch64/lib/")

#################
# TARGET OUTPUT #
#################
SET(TARGET_OUTPUT SHARED)
# SET(TARGET_OUTPUT STATIC)
# SET(TARGET_OUTPUT EXECUTE)

