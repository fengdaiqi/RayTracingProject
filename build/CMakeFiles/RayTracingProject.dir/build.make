# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = F:\Cmake\bin\cmake.exe

# The command to remove a file.
RM = F:\Cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\TA_library\RayTracingProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\TA_library\RayTracingProject\build

# Include any dependencies generated for this target.
include CMakeFiles/RayTracingProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RayTracingProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RayTracingProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RayTracingProject.dir/flags.make

CMakeFiles/RayTracingProject.dir/main.cpp.obj: CMakeFiles/RayTracingProject.dir/flags.make
CMakeFiles/RayTracingProject.dir/main.cpp.obj: E:/TA_library/RayTracingProject/main.cpp
CMakeFiles/RayTracingProject.dir/main.cpp.obj: CMakeFiles/RayTracingProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\TA_library\RayTracingProject\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RayTracingProject.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracingProject.dir/main.cpp.obj -MF CMakeFiles\RayTracingProject.dir\main.cpp.obj.d -o CMakeFiles\RayTracingProject.dir\main.cpp.obj -c E:\TA_library\RayTracingProject\main.cpp

CMakeFiles/RayTracingProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracingProject.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\TA_library\RayTracingProject\main.cpp > CMakeFiles\RayTracingProject.dir\main.cpp.i

CMakeFiles/RayTracingProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracingProject.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\TA_library\RayTracingProject\main.cpp -o CMakeFiles\RayTracingProject.dir\main.cpp.s

# Object files for target RayTracingProject
RayTracingProject_OBJECTS = \
"CMakeFiles/RayTracingProject.dir/main.cpp.obj"

# External object files for target RayTracingProject
RayTracingProject_EXTERNAL_OBJECTS =

RayTracingProject.exe: CMakeFiles/RayTracingProject.dir/main.cpp.obj
RayTracingProject.exe: CMakeFiles/RayTracingProject.dir/build.make
RayTracingProject.exe: CMakeFiles/RayTracingProject.dir/linkLibs.rsp
RayTracingProject.exe: CMakeFiles/RayTracingProject.dir/objects1.rsp
RayTracingProject.exe: CMakeFiles/RayTracingProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\TA_library\RayTracingProject\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RayTracingProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RayTracingProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RayTracingProject.dir/build: RayTracingProject.exe
.PHONY : CMakeFiles/RayTracingProject.dir/build

CMakeFiles/RayTracingProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RayTracingProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/RayTracingProject.dir/clean

CMakeFiles/RayTracingProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\TA_library\RayTracingProject E:\TA_library\RayTracingProject E:\TA_library\RayTracingProject\build E:\TA_library\RayTracingProject\build E:\TA_library\RayTracingProject\build\CMakeFiles\RayTracingProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RayTracingProject.dir/depend

