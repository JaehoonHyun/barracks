############################      HOW TO USE       ##################################
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-android.cmake -DCMAKE_TARGET=SHARED  #
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-android.cmake -DCMAKE_TARGET=STATIC  #
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-android.cmake -DCMAKE_TARGET=EXECUTE #
#####################################################################################

###############
# SYSTEM INFO #
###############
SET(CMAKE_SYSTEM_NAME Android)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR "aarch64")

#######################
# CMAKE COMPILER INFO #
#######################
# SET(CMAKE_ANDROID_STANDALONE_TOOLCHAIN ${CMAKE_ANDROID_SYSROOT_PATH})
# SET(CMAKE_SYSROOT ${CMAKE_ANDROID_SYSROOT_PATH})

# NOTE: It depend on toolchain path of setup_android_env.sh
SET(HOME $ENV{HOME})

SET(CMAKE_C_COMPILER        ${HOME}/Android/android_toolchain/bin/aarch64-linux-android-gcc)
SET(CMAKE_CXX_COMPILER      ${HOME}/Android/android_toolchain/bin/aarch64-linux-android-g++)
SET(CMAKE_CPP_COMPILER      ${HOME}/Android/android_toolchain/bin/aarch64-linux-android-cpp)
SET(CMAKE_C_COMPILER_AR     ${HOME}/Android/android_toolchain/bin/aarch64-linux-android-ar)
SET(CMAKE_C_COMPILER_RANLIB ${HOME}/Android/android_toolchain/bin/aarch64-linux-android-ranlib)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


###########################
# External Library Header #
###########################
SET(EXT_LIB_HEADER /usr/local/aarch64/include
                   /usr/local/aarch64/sdk/native/jni/include)

#############################
# External Library Location #
#############################
SET (EXTERNAL_LINK_LIB  
                        /usr/local/aarch64/lib/libzmq.so
                        /usr/local/aarch64/lib/libpistache.a
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_core.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_imgcodecs.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_imgproc.so                         
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_highgui.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_xfeatures2d.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_flann.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_videoio.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_ml.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_shape.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_calib3d.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_video.so
                        /usr/local/aarch64/sdk/native/libs/arm64-v8a/libopencv_features2d.so
                        )


#############################
# Standard Library Location #
#############################
# SET (STANDARD_LINK_LIB  log 
#                        gnustl_shared)

########
# link #
########
# SET(MY_LINK_DIRECTORIES  "-L/usr/local/aarch64 -L/usr/local/aarch64/lib/")

#################
# TARGET OUTPUT #
#################
# SET(TARGET_OUTPUT SHARED)
# SET(TARGET_OUTPUT STATIC)
# SET(TARGET_OUTPUT EXECUTE)
SET(TARGET_OUTPUT ${CMAKE_TARGET})


