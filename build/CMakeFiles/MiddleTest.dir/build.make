# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lenmac/Documents/Lab/ClionProjects/Middle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lenmac/Documents/Lab/ClionProjects/Middle/build

# Include any dependencies generated for this target.
include CMakeFiles/MiddleTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MiddleTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MiddleTest.dir/flags.make

CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o: ../src/Main_Test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Main_Test.cpp

CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Main_Test.cpp > CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.i

CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Main_Test.cpp -o CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.s

CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o


CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o: ../src/MessageMonitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/MessageMonitor.cpp

CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/MessageMonitor.cpp > CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.i

CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/MessageMonitor.cpp -o CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.s

CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o


CMakeFiles/MiddleTest.dir/src/Middle.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/Middle.cpp.o: ../src/Middle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MiddleTest.dir/src/Middle.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/Middle.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Middle.cpp

CMakeFiles/MiddleTest.dir/src/Middle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/Middle.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Middle.cpp > CMakeFiles/MiddleTest.dir/src/Middle.cpp.i

CMakeFiles/MiddleTest.dir/src/Middle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/Middle.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Middle.cpp -o CMakeFiles/MiddleTest.dir/src/Middle.cpp.s

CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/Middle.cpp.o


CMakeFiles/MiddleTest.dir/src/Server.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/Server.cpp.o: ../src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MiddleTest.dir/src/Server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/Server.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Server.cpp

CMakeFiles/MiddleTest.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/Server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Server.cpp > CMakeFiles/MiddleTest.dir/src/Server.cpp.i

CMakeFiles/MiddleTest.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/Server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Server.cpp -o CMakeFiles/MiddleTest.dir/src/Server.cpp.s

CMakeFiles/MiddleTest.dir/src/Server.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/Server.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/Server.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/Server.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/Server.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/Server.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/Server.cpp.o


CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o: ../src/ServerManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/ServerManager.cpp

CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/ServerManager.cpp > CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.i

CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/ServerManager.cpp -o CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.s

CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o


CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o: ../src/Terminal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Terminal.cpp

CMakeFiles/MiddleTest.dir/src/Terminal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/Terminal.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Terminal.cpp > CMakeFiles/MiddleTest.dir/src/Terminal.cpp.i

CMakeFiles/MiddleTest.dir/src/Terminal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/Terminal.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Terminal.cpp -o CMakeFiles/MiddleTest.dir/src/Terminal.cpp.s

CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o


CMakeFiles/MiddleTest.dir/src/Message.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/Message.cpp.o: ../src/Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MiddleTest.dir/src/Message.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/Message.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Message.cpp

CMakeFiles/MiddleTest.dir/src/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/Message.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Message.cpp > CMakeFiles/MiddleTest.dir/src/Message.cpp.i

CMakeFiles/MiddleTest.dir/src/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/Message.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/Message.cpp -o CMakeFiles/MiddleTest.dir/src/Message.cpp.s

CMakeFiles/MiddleTest.dir/src/Message.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/Message.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/Message.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/Message.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/Message.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/Message.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/Message.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/Message.cpp.o


CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o: ../src/TransmitUnit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/TransmitUnit.cpp

CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/TransmitUnit.cpp > CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.i

CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/TransmitUnit.cpp -o CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.s

CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o


CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o: ../src/AuthorityManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/AuthorityManager.cpp

CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/AuthorityManager.cpp > CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.i

CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/AuthorityManager.cpp -o CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.s

CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o


CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o: CMakeFiles/MiddleTest.dir/flags.make
CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o: ../src/MessageRegisterAck.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o -c /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/MessageRegisterAck.cpp

CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/MessageRegisterAck.cpp > CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.i

CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lenmac/Documents/Lab/ClionProjects/Middle/src/MessageRegisterAck.cpp -o CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.s

CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.requires:

.PHONY : CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.requires

CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.provides: CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.requires
	$(MAKE) -f CMakeFiles/MiddleTest.dir/build.make CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.provides.build
.PHONY : CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.provides

CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.provides.build: CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o


# Object files for target MiddleTest
MiddleTest_OBJECTS = \
"CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/Middle.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/Server.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/Message.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o" \
"CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o"

# External object files for target MiddleTest
MiddleTest_EXTERNAL_OBJECTS =

MiddleTest: CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/Middle.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/Server.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/Message.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o
MiddleTest: CMakeFiles/MiddleTest.dir/build.make
MiddleTest: CMakeFiles/MiddleTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable MiddleTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MiddleTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MiddleTest.dir/build: MiddleTest

.PHONY : CMakeFiles/MiddleTest.dir/build

CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/Main_Test.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/MessageMonitor.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/Middle.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/Server.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/ServerManager.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/Terminal.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/Message.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/TransmitUnit.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/AuthorityManager.cpp.o.requires
CMakeFiles/MiddleTest.dir/requires: CMakeFiles/MiddleTest.dir/src/MessageRegisterAck.cpp.o.requires

.PHONY : CMakeFiles/MiddleTest.dir/requires

CMakeFiles/MiddleTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MiddleTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MiddleTest.dir/clean

CMakeFiles/MiddleTest.dir/depend:
	cd /Users/lenmac/Documents/Lab/ClionProjects/Middle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lenmac/Documents/Lab/ClionProjects/Middle /Users/lenmac/Documents/Lab/ClionProjects/Middle /Users/lenmac/Documents/Lab/ClionProjects/Middle/build /Users/lenmac/Documents/Lab/ClionProjects/Middle/build /Users/lenmac/Documents/Lab/ClionProjects/Middle/build/CMakeFiles/MiddleTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MiddleTest.dir/depend
