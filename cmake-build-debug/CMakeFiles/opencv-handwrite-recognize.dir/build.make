# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pjl/opencv-handwrite-recognize

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pjl/opencv-handwrite-recognize/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/opencv-handwrite-recognize.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opencv-handwrite-recognize.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opencv-handwrite-recognize.dir/flags.make

CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o: CMakeFiles/opencv-handwrite-recognize.dir/flags.make
CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pjl/opencv-handwrite-recognize/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o -c /Users/pjl/opencv-handwrite-recognize/main.cpp

CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pjl/opencv-handwrite-recognize/main.cpp > CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.i

CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pjl/opencv-handwrite-recognize/main.cpp -o CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.s

CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.requires

CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.provides: CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/opencv-handwrite-recognize.dir/build.make CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.provides

CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.provides.build: CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o


CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o: CMakeFiles/opencv-handwrite-recognize.dir/flags.make
CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o: ../mousedraw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pjl/opencv-handwrite-recognize/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o -c /Users/pjl/opencv-handwrite-recognize/mousedraw.cpp

CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pjl/opencv-handwrite-recognize/mousedraw.cpp > CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.i

CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pjl/opencv-handwrite-recognize/mousedraw.cpp -o CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.s

CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.requires:

.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.requires

CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.provides: CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.requires
	$(MAKE) -f CMakeFiles/opencv-handwrite-recognize.dir/build.make CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.provides.build
.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.provides

CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.provides.build: CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o


CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o: CMakeFiles/opencv-handwrite-recognize.dir/flags.make
CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o: ../train.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pjl/opencv-handwrite-recognize/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o -c /Users/pjl/opencv-handwrite-recognize/train.cpp

CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pjl/opencv-handwrite-recognize/train.cpp > CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.i

CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pjl/opencv-handwrite-recognize/train.cpp -o CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.s

CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.requires:

.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.requires

CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.provides: CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.requires
	$(MAKE) -f CMakeFiles/opencv-handwrite-recognize.dir/build.make CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.provides.build
.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.provides

CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.provides.build: CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o


# Object files for target opencv-handwrite-recognize
opencv__handwrite__recognize_OBJECTS = \
"CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o" \
"CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o" \
"CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o"

# External object files for target opencv-handwrite-recognize
opencv__handwrite__recognize_EXTERNAL_OBJECTS =

opencv-handwrite-recognize: CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o
opencv-handwrite-recognize: CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o
opencv-handwrite-recognize: CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o
opencv-handwrite-recognize: CMakeFiles/opencv-handwrite-recognize.dir/build.make
opencv-handwrite-recognize: /usr/local/lib/libopencv_videostab.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_ts.a
opencv-handwrite-recognize: /usr/local/lib/libopencv_superres.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_stitching.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_contrib.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_nonfree.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_ocl.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_gpu.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_photo.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_objdetect.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_legacy.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_video.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_ml.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_calib3d.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_features2d.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_highgui.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_imgproc.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_flann.2.4.13.dylib
opencv-handwrite-recognize: /usr/local/lib/libopencv_core.2.4.13.dylib
opencv-handwrite-recognize: CMakeFiles/opencv-handwrite-recognize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pjl/opencv-handwrite-recognize/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable opencv-handwrite-recognize"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opencv-handwrite-recognize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opencv-handwrite-recognize.dir/build: opencv-handwrite-recognize

.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/build

CMakeFiles/opencv-handwrite-recognize.dir/requires: CMakeFiles/opencv-handwrite-recognize.dir/main.cpp.o.requires
CMakeFiles/opencv-handwrite-recognize.dir/requires: CMakeFiles/opencv-handwrite-recognize.dir/mousedraw.cpp.o.requires
CMakeFiles/opencv-handwrite-recognize.dir/requires: CMakeFiles/opencv-handwrite-recognize.dir/train.cpp.o.requires

.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/requires

CMakeFiles/opencv-handwrite-recognize.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opencv-handwrite-recognize.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/clean

CMakeFiles/opencv-handwrite-recognize.dir/depend:
	cd /Users/pjl/opencv-handwrite-recognize/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pjl/opencv-handwrite-recognize /Users/pjl/opencv-handwrite-recognize /Users/pjl/opencv-handwrite-recognize/cmake-build-debug /Users/pjl/opencv-handwrite-recognize/cmake-build-debug /Users/pjl/opencv-handwrite-recognize/cmake-build-debug/CMakeFiles/opencv-handwrite-recognize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opencv-handwrite-recognize.dir/depend

