cmake_minimum_required(VERSION 3.21)
project(Blockchain)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-O2")
endif()

set(SOURCE_FILES main.cpp)
add_executable(Blockchain ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(Blockchain Blockchain_src)
