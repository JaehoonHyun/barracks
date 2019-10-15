############################      HOW TO USE       #################################
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-native.cmake -DCMAKE_TARGET=SHARED  #
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-native.cmake -DCMAKE_TARGET=STATIC  #
# cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-native.cmake -DCMAKE_TARGET=EXECUTE #
####################################################################################

###############
# SYSTEM INFO #
###############
SET(CMAKE_SYSTEM_VERSION 1)

#######################
# CMAKE COMPILER INFO #
#######################
SET(CMAKE_C_COMPILER         "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER       "/usr/bin/g++")
SET(CMAKE_CPP_COMPILER       "/usr/bin/cpp")
SET(CMAKE_C_COMPILER_AR      "/usr/bin/ar")
SET(CMAKE_C_COMPILER_RANLIB  "/usr/bin/ranlib")

###########################
# External Library Header #
###########################
SET(EXT_LIB_HEADER /usr/local/include
                   )

#############################
# External Library Location #
#############################
SET (EXTERNAL_LINK_LIB
#                       /usr/local/lib/libzmq.so
#                       /usr/local/lib/libpistache.a
#                       /usr/local/lib/libopencv_core.so.3.4.2
#                       /usr/local/lib/libopencv_imgcodecs.so
#                       /usr/local/lib/libopencv_imgproc.so
#                       /usr/local/lib/libopencv_highgui.so
#                       /usr/local/lib/libopencv_xfeatures2d.so
#                       /usr/local/lib/libopencv_flann.so
#                       /usr/local/lib/libopencv_videoio.so
#                       /usr/local/lib/libopencv_ml.so
#                       /usr/local/lib/libopencv_shape.so
#                       /usr/local/lib/libopencv_calib3d.so
#                       /usr/local/lib/libopencv_video.so
#                       /usr/local/lib/libopencv_features2d.so
                        )


#############################
# Standard Library Location #
#############################
#SET (STANDARD_LINK_LIB  log 
#                        gnustl_shared)

########
# link #
########
# SET(MY_LINK_DIRECTORIES  "-L/usr/local/lib")

#################
# TARGET OUTPUT #
#################
# SET(TARGET_OUTPUT SHARED)
# SET(TARGET_OUTPUT STATIC)
# SET(TARGET_OUTPUT EXECUTE)
SET(TARGET_OUTPUT ${CMAKE_TARGET})

