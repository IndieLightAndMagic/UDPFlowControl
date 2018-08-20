cmake_minimum_required(VERSION 3.5.1)

project(UDPFC VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 14)


get_filename_component(TESTFILES_DIR "${CMAKE_SOURCE_DIR}/testfiles" ABSOLUTE)
get_filename_component(3RD_INC_DIR "${CMAKE_SOURCE_DIR}/3rd/include" ABSOLUTE)
get_filename_component(3RD_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd/lib" ABSOLUTE)


add_executable(udpfc_test udpfc_test.cpp)

include_directories(udpfc_test ${3RD_INC_DIR})
target_compile_definitions(udpfc_test PRIVATE -DTESTFILES_DIR=\"${TESTFILES_DIR}\")

target_link_libraries(udpfc_test ${3RD_LIB_DIR}/libUDPServer.a)

#add_executable(udpservertest udpservertest.cpp udpserver.cpp)

#add_library(UDPServer STATIC udpserver.cpp udpserver.h udpclient.cpp udpclient.h)

