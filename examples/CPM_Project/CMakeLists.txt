cmake_minimum_required(VERSION 3.21.0)
project(fetchcontent_slap_example VERSION 0.1 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
include(CMakePrintHelpers)

if (PROJECT_IS_TOP_LEVEL)
  include(FindCPM)
  FetchContent_Declare(libslap
    GIT_REPOSITORY https://github.com/bjack205/slap
    GIT_TAG main
  )
  set(SLAP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(libslap)
endif()


add_executable(fetchcontent_slap_example ../getting_started.c)
target_link_libraries(fetchcontent_slap_example slap::slap)
