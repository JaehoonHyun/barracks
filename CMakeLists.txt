cmake_minimum_required (VERSION 3.2)


######################
# PROJECT PROPERTIES #
######################
message("== barracks ==")
project (barracks)
SET ( OUTPUT_ELF ${PROJECT_NAME} )
SET (WORKSPACE ".")
SET (PROJECT_NAME "barracks")
SET (CMAKE_BUILD_TYPE Debug)
# SET ( CMAKE_BUILD_TYPE Release)


##################
# LOG CMAKE ARCH #
##################
message ("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message ("CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message ("USR_PATH: ${USR_PATH}")
message ("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message ("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")



#####################
# WORKSPACE INCLUDE #
#####################
include_directories (${WORKSPACE})
include_directories (${WORKSPACE}/gtest)
include_directories (${WORKSPACE}/gtest/include)

#################
# ADD SRC FILES #
#################
file(GLOB_RECURSE COMMON_SRC_FILES ${WORKSPACE}/common/src/*.cpp)
file(GLOB_RECURSE MY_CLAY_FILES clay/src/*.cpp)
file(GLOB_RECURSE MY_SRC_FILES src/*.cpp)
file(GLOB_RECURSE MY_SRC_FILES src/*.cc)
file(GLOB_RECURSE G_TEST_FILES gtest/src/gtest-all.cc)
SET (SRC_FILES ${COMMON_SRC_FILES} 
               ${MY_CLAY_FILES}
               ${MY_SRC_FILES}
               ${G_TEST_FILES}
               )
message("SRC_FILES: ${SRC_FILES}")


####################
# SRC Definitions #
####################
add_definitions(-DLOG_LEVEL_E=12)
add_definitions(-DLOG_LEVEL_I=14)
add_definitions(-DLOG_LEVEL_D=15)
add_definitions(-DLOG_LEVEL=LOG_LEVEL_D)
add_definitions(-DLOG_FILE=stdout)
add_definitions(-DPWD_BIN="${CMAKE_CURRENT_BINARY_DIR}")
add_definitions(-DPWD_SRC="${CMAKE_CURRENT_SOURCE_DIR}")

#############
# CXX FLAGS #
#############
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -O0 -Wall -fPIC ${MY_LINK_DIRECTORIES}")

###########################
# External Library Header #
###########################
include_directories (${EXT_LIB_HEADER})


####################
# C++ STANDARD VER #
####################


########
# link #
########
link_directories( /usr/local/aarch64/lib/ )

###########
# package #
###########
# find_package (Threads REQUIRED)


#################
# OUTPUT BINARY #
#################
if (TARGET_OUTPUT STREQUAL SHARED)
  add_library(${OUTPUT_ELF} SHARED  ${SRC_FILES})
  target_link_libraries(${OUTPUT_ELF} ${STANDARD_LINK_LIB} 
                                      ${EXTERNAL_LINK_LIB})
elseif (TARGET_OUTPUT STREQUAL STATIC)

  add_library(${OUTPUT_ELF} STATIC ${SRC_FILES})
  target_link_libraries(${OUTPUT_ELF} ${STANDARD_LINK_LIB} 
                                      ${EXTERNAL_LINK_LIB})
elseif (TARGET_OUTPUT STREQUAL EXECUTE)

  add_executable(${OUTPUT_ELF} ${SRC_FILES} 
                               ./main.cpp)
  target_link_libraries(${OUTPUT_ELF} ${STANDARD_LINK_LIB} 
                                      ${EXTERNAL_LINK_LIB})
endif ()



