cmake_minimum_required(VERSION 3.20)
project(RayTracingProject LANGUAGES CXX )


# Set to C++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

#Source
set(SOURCE_ONE_WEEKEND 
    src/InOneWeekend/main.cpp
    
    src/InOneWeekend/test.h
)

include_directories(src)

add_executable(inOneWeekend  ${SOURCE_ONE_WEEKEND})