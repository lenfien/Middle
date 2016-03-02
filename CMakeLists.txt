cmake_minimum_required(VERSION 3.3)
project(Middle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

INCLUDE_DIRECTORIES(inc)
set(HEADER_FILES
        src/Debug.h
        src/Message.h
        src/MessageMonitor.h
        src/Middle.h
        src/Net.h
        src/Server.h
        src/ServerManager.h
        src/Terminal.h
        src/Exceptions.h
        src/TransmitUnit.h
        src/AuthorityManager.h src/Autolock.h)

set(SOURCE_FILES
        src/MessageMonitor.cpp
        src/Middle.cpp
        src/Server.cpp
        src/ServerManager.cpp
        src/Terminal.cpp
        src/Message.cpp
        src/TransmitUnit.cpp
        src/AuthorityManager.cpp
        src/MessageRegisterAck.cpp)

add_executable(Middle src/Main.cpp ${SOURCE_FILES} ${HEADER_FILES})
add_executable(MiddleTest src/Main_Test.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Middle pthread)
target_link_libraries(MiddleTest pthread)