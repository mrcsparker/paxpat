cmake_minimum_required(VERSION 3.3)
project(paxpat)

find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    paxpat/Expat.hpp
    CMakeLists.txt
    LICENSE
    paxpat/main.cpp
    README.md)

add_executable(paxpat ${SOURCE_FILES})

target_link_libraries(paxpat ${EXPAT_LIBRARIES})
