cmake_minimum_required(VERSION 3.0.0)
project(slap_examples VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)
FetchContent_Declare(slap
        GIT_REPOSITORY https://github.com/bjack205/slap
        GIT_TAG pass-by-value)

add_executable(getting_started getting_started.c)