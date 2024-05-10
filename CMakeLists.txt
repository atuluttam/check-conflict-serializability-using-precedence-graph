cmake_minimum_required(VERSION 3.10)
# include_directories("/usr/local/include/opencv4")

project(CPPComponents VERSION 0.1
		DESCRIPTION "sample repo for demo")

# set(CMAKE_C_COMPILER "/usr/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  MESSAGE(STATUS "it's clang")
  set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy"
    "-header-filter=."
    "-checks='-*,modernize-*,cppcoreguidelines-*,-modernize-use-trailing-return-type")
endif()

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS  "-Wall -Wextra")
# find_package( OpenCV)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS} )
add_executable(CPPComponents src/interface.cpp)

add_subdirectory(libs)
# target_link_libraries(CPPComponents DataOps ${OpenCV_LIBS})

target_include_directories(CPPComponents PUBLIC include)
