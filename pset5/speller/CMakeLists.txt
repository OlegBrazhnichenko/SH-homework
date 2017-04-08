cmake_minimum_required(VERSION 3.6)
project(speller)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ArrayList.cpp ArrayList.h LinkedList.cpp LinkedList.h Node.cpp Node.h Dictionary.cpp Dictionary.h Trecker.cpp Trecker.h)
add_executable(speller ${SOURCE_FILES})