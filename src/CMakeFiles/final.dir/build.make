# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/orps/temp/cpp/cpp_wserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orps/temp/cpp/cpp_wserver

# Include any dependencies generated for this target.
include src/CMakeFiles/final.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/final.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/final.dir/flags.make

src/CMakeFiles/final.dir/listener.cpp.o: src/CMakeFiles/final.dir/flags.make
src/CMakeFiles/final.dir/listener.cpp.o: src/listener.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/orps/temp/cpp/cpp_wserver/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/final.dir/listener.cpp.o"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/final.dir/listener.cpp.o -c /home/orps/temp/cpp/cpp_wserver/src/listener.cpp

src/CMakeFiles/final.dir/listener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/listener.cpp.i"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/orps/temp/cpp/cpp_wserver/src/listener.cpp > CMakeFiles/final.dir/listener.cpp.i

src/CMakeFiles/final.dir/listener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/listener.cpp.s"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/orps/temp/cpp/cpp_wserver/src/listener.cpp -o CMakeFiles/final.dir/listener.cpp.s

src/CMakeFiles/final.dir/listener.cpp.o.requires:
.PHONY : src/CMakeFiles/final.dir/listener.cpp.o.requires

src/CMakeFiles/final.dir/listener.cpp.o.provides: src/CMakeFiles/final.dir/listener.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/final.dir/build.make src/CMakeFiles/final.dir/listener.cpp.o.provides.build
.PHONY : src/CMakeFiles/final.dir/listener.cpp.o.provides

src/CMakeFiles/final.dir/listener.cpp.o.provides.build: src/CMakeFiles/final.dir/listener.cpp.o

src/CMakeFiles/final.dir/main.cpp.o: src/CMakeFiles/final.dir/flags.make
src/CMakeFiles/final.dir/main.cpp.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/orps/temp/cpp/cpp_wserver/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/final.dir/main.cpp.o"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/final.dir/main.cpp.o -c /home/orps/temp/cpp/cpp_wserver/src/main.cpp

src/CMakeFiles/final.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/main.cpp.i"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/orps/temp/cpp/cpp_wserver/src/main.cpp > CMakeFiles/final.dir/main.cpp.i

src/CMakeFiles/final.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/main.cpp.s"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/orps/temp/cpp/cpp_wserver/src/main.cpp -o CMakeFiles/final.dir/main.cpp.s

src/CMakeFiles/final.dir/main.cpp.o.requires:
.PHONY : src/CMakeFiles/final.dir/main.cpp.o.requires

src/CMakeFiles/final.dir/main.cpp.o.provides: src/CMakeFiles/final.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/final.dir/build.make src/CMakeFiles/final.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/final.dir/main.cpp.o.provides

src/CMakeFiles/final.dir/main.cpp.o.provides.build: src/CMakeFiles/final.dir/main.cpp.o

src/CMakeFiles/final.dir/httphandler.cpp.o: src/CMakeFiles/final.dir/flags.make
src/CMakeFiles/final.dir/httphandler.cpp.o: src/httphandler.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/orps/temp/cpp/cpp_wserver/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/final.dir/httphandler.cpp.o"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/final.dir/httphandler.cpp.o -c /home/orps/temp/cpp/cpp_wserver/src/httphandler.cpp

src/CMakeFiles/final.dir/httphandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/httphandler.cpp.i"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/orps/temp/cpp/cpp_wserver/src/httphandler.cpp > CMakeFiles/final.dir/httphandler.cpp.i

src/CMakeFiles/final.dir/httphandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/httphandler.cpp.s"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/orps/temp/cpp/cpp_wserver/src/httphandler.cpp -o CMakeFiles/final.dir/httphandler.cpp.s

src/CMakeFiles/final.dir/httphandler.cpp.o.requires:
.PHONY : src/CMakeFiles/final.dir/httphandler.cpp.o.requires

src/CMakeFiles/final.dir/httphandler.cpp.o.provides: src/CMakeFiles/final.dir/httphandler.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/final.dir/build.make src/CMakeFiles/final.dir/httphandler.cpp.o.provides.build
.PHONY : src/CMakeFiles/final.dir/httphandler.cpp.o.provides

src/CMakeFiles/final.dir/httphandler.cpp.o.provides.build: src/CMakeFiles/final.dir/httphandler.cpp.o

src/CMakeFiles/final.dir/server.cpp.o: src/CMakeFiles/final.dir/flags.make
src/CMakeFiles/final.dir/server.cpp.o: src/server.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/orps/temp/cpp/cpp_wserver/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/final.dir/server.cpp.o"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/final.dir/server.cpp.o -c /home/orps/temp/cpp/cpp_wserver/src/server.cpp

src/CMakeFiles/final.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/server.cpp.i"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/orps/temp/cpp/cpp_wserver/src/server.cpp > CMakeFiles/final.dir/server.cpp.i

src/CMakeFiles/final.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/server.cpp.s"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/orps/temp/cpp/cpp_wserver/src/server.cpp -o CMakeFiles/final.dir/server.cpp.s

src/CMakeFiles/final.dir/server.cpp.o.requires:
.PHONY : src/CMakeFiles/final.dir/server.cpp.o.requires

src/CMakeFiles/final.dir/server.cpp.o.provides: src/CMakeFiles/final.dir/server.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/final.dir/build.make src/CMakeFiles/final.dir/server.cpp.o.provides.build
.PHONY : src/CMakeFiles/final.dir/server.cpp.o.provides

src/CMakeFiles/final.dir/server.cpp.o.provides.build: src/CMakeFiles/final.dir/server.cpp.o

src/CMakeFiles/final.dir/worker.cpp.o: src/CMakeFiles/final.dir/flags.make
src/CMakeFiles/final.dir/worker.cpp.o: src/worker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/orps/temp/cpp/cpp_wserver/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/final.dir/worker.cpp.o"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/final.dir/worker.cpp.o -c /home/orps/temp/cpp/cpp_wserver/src/worker.cpp

src/CMakeFiles/final.dir/worker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/worker.cpp.i"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/orps/temp/cpp/cpp_wserver/src/worker.cpp > CMakeFiles/final.dir/worker.cpp.i

src/CMakeFiles/final.dir/worker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/worker.cpp.s"
	cd /home/orps/temp/cpp/cpp_wserver/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/orps/temp/cpp/cpp_wserver/src/worker.cpp -o CMakeFiles/final.dir/worker.cpp.s

src/CMakeFiles/final.dir/worker.cpp.o.requires:
.PHONY : src/CMakeFiles/final.dir/worker.cpp.o.requires

src/CMakeFiles/final.dir/worker.cpp.o.provides: src/CMakeFiles/final.dir/worker.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/final.dir/build.make src/CMakeFiles/final.dir/worker.cpp.o.provides.build
.PHONY : src/CMakeFiles/final.dir/worker.cpp.o.provides

src/CMakeFiles/final.dir/worker.cpp.o.provides.build: src/CMakeFiles/final.dir/worker.cpp.o

# Object files for target final
final_OBJECTS = \
"CMakeFiles/final.dir/listener.cpp.o" \
"CMakeFiles/final.dir/main.cpp.o" \
"CMakeFiles/final.dir/httphandler.cpp.o" \
"CMakeFiles/final.dir/server.cpp.o" \
"CMakeFiles/final.dir/worker.cpp.o"

# External object files for target final
final_EXTERNAL_OBJECTS =

final: src/CMakeFiles/final.dir/listener.cpp.o
final: src/CMakeFiles/final.dir/main.cpp.o
final: src/CMakeFiles/final.dir/httphandler.cpp.o
final: src/CMakeFiles/final.dir/server.cpp.o
final: src/CMakeFiles/final.dir/worker.cpp.o
final: src/CMakeFiles/final.dir/build.make
final: src/CMakeFiles/final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../final"
	cd /home/orps/temp/cpp/cpp_wserver/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/final.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/final.dir/build: final
.PHONY : src/CMakeFiles/final.dir/build

src/CMakeFiles/final.dir/requires: src/CMakeFiles/final.dir/listener.cpp.o.requires
src/CMakeFiles/final.dir/requires: src/CMakeFiles/final.dir/main.cpp.o.requires
src/CMakeFiles/final.dir/requires: src/CMakeFiles/final.dir/httphandler.cpp.o.requires
src/CMakeFiles/final.dir/requires: src/CMakeFiles/final.dir/server.cpp.o.requires
src/CMakeFiles/final.dir/requires: src/CMakeFiles/final.dir/worker.cpp.o.requires
.PHONY : src/CMakeFiles/final.dir/requires

src/CMakeFiles/final.dir/clean:
	cd /home/orps/temp/cpp/cpp_wserver/src && $(CMAKE_COMMAND) -P CMakeFiles/final.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/final.dir/clean

src/CMakeFiles/final.dir/depend:
	cd /home/orps/temp/cpp/cpp_wserver && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orps/temp/cpp/cpp_wserver /home/orps/temp/cpp/cpp_wserver/src /home/orps/temp/cpp/cpp_wserver /home/orps/temp/cpp/cpp_wserver/src /home/orps/temp/cpp/cpp_wserver/src/CMakeFiles/final.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/final.dir/depend

