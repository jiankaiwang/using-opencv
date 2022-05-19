cmake_minimum_required(VERSION 3.0)

project(main VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE FALSE)

set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../opencv/build)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

FILE(GLOB LIB_HEADERS *.hpp)
FILE(GLOB LIB_SOURCES helper.cpp)
add_library(res ${LIB_HEADERS} ${LIB_SOURCES})

add_executable(main dft_filters.cc)

include_directories(main ${OpenCV_INCLUDE_DIRS})

target_link_libraries(main PUBLIC ${OpenCV_LIBS})
target_link_libraries(main PUBLIC res)
