cmake_minimum_required(VERSION 3.21.0)
project(cpm_slap_example LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FindCPM.cmake)

if (PROJECT_IS_TOP_LEVEL)
  CPMAddPackage(
    NAME slap
    GIT_REPOSITORY bjack205/slap
    VERSION main
    OPTIONS
    SLAP_BUILD_TESTS OFF
  )
endif()

add_executable(cpm_slap_example ../getting_started.c)
target_link_libraries(cpm_slap_example PRIVATE slap::slap)