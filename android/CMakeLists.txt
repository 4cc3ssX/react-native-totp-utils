project(TotpUtils)
cmake_minimum_required(VERSION 3.9.0)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)

add_library(cpp
            SHARED
            ../../react-native/ReactCommon/jsi/jsi/jsi.cpp
            ../cpp/react-native-totp-utils.cpp
            cpp-adapter.cpp
)

# Specifies a path to native header files.
include_directories(
            ../../react-native/React
            ../../react-native/React/Base
            ../../react-native/ReactCommon/jsi
            ../cpp
)

set_target_properties(
        cpp PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(
        cpp
        android
)
