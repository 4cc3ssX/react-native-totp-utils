project(TotpUtils)
cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "react-native-totp-utils")
set (BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)

# Totp example cannot compile with ../.. use ../node_modules
set(NODE_MODULES_DIR ../..)

add_library(reactnativetotputils
            SHARED
            ${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp
            ../cpp/react-native-totp-utils.cpp
            cpp-adapter.cpp
)

# Specifies a path to native header files.
include_directories(
            ${NODE_MODULES_DIR}/react-native/React
            ${NODE_MODULES_DIR}/react-native/React/Base
            ${NODE_MODULES_DIR}/react-native/ReactCommon/jsi
            ../cpp
)

set_target_properties(
        reactnativetotputils PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(
        reactnativetotputils
        android             # <-- Android JNI core
)
