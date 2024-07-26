cmake_minimum_required(VERSION 3.20)
project(RayTracingProject LANGUAGES CXX )


# Set to C++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

#Source

set ( EXTERNAL
  src/external/stb_image.h
)

set(SOURCE_ONE_WEEKEND 

src/InOneWeekend/camera.h
src/InOneWeekend/color.h
src/InOneWeekend/hittable.h
src/InOneWeekend/hittable_list.h
src/InOneWeekend/interval.h
src/InOneWeekend/material.h
src/InOneWeekend/ray.h

src/InOneWeekend/rtweekend.h
src/InOneWeekend/sphere.h
src/InOneWeekend/vec3.h

src/InOneWeekend/main.cpp
)

set(SOURCE_NEXT_WEEK 
src/external/stb_image.h
src/TheNextWeek/camera.h
src/TheNextWeek/color.h
src/TheNextWeek/hittable.h
src/TheNextWeek/hittable_list.h
src/TheNextWeek/interval.h
src/TheNextWeek/material.h
src/TheNextWeek/ray.h
src/TheNextWeek/aabb.h
src/TheNextWeek/bvh.h
src/TheNextWeek/rtweekend.h
src/TheNextWeek/sphere.h
src/TheNextWeek/vec3.h
src/TheNextWeek/texture.h
src/TheNextWeek/rtw_stb_image.h
src/TheNextWeek/perlin.h
src/TheNextWeek/quad.h

src/TheNextWeek/main.cpp
)

include_directories(src)

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # /wd #### - Disable warning
    # /we #### - treat warning as error
    add_compile_options("/W4")      # Enable level-4 warnings
    add_compile_options("/we 4265") # Class has virtual functions, but its non-trivial destructor is not virtual
    add_compile_options("/we 5204") # Class has virtual functions, but its trivial destructor is not virtual
    add_compile_options("/wd 4100") # unreferenced formal parameter
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
endif()



add_executable(inOneWeekend       ${SOURCE_ONE_WEEKEND})
add_executable(TheNextWeek       ${SOURCE_NEXT_WEEK})