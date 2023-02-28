cmake_minimum_required(VERSION 3.0.0)
project(slap_examples VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

#include(CPM.cmake)
#CPMAddPackage("gh:bjack205/slap#main")

add_executable(getting_started ../getting_started.c)
target_link_libraries(getting_started PRIVATE slap)