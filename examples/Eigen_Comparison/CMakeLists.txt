cmake_minimum_required(VERSION 3.21.0)
project(slap_eigen_comparison LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


if (PROJECT_IS_TOP_LEVEL)
  include(../CPM_project/FindCPM.cmake)
  CPMAddPackage(
    NAME slap
    GIT_REPOSITORY bjack205/slap
    VERSION main
    OPTIONS
    SLAP_BUILD_TESTS OFF
  )
endif()

CPMAddPackage(
  NAME Eigen
  VERSION 3.4.0
  URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
  # Eigen's CMakelists are not intended for library use
  DOWNLOAD_ONLY YES
)
if(Eigen_ADDED)
  add_library(Eigen::Eigen INTERFACE IMPORTED)
  target_include_directories(Eigen::Eigen INTERFACE ${Eigen_SOURCE_DIR})
endif()

CPMAddPackage("gh:fmtlib/fmt#9.1.0")

cmake_print_variables(CMAKE_C_FLAGS_RELWITHDEBINFO)
cmake_print_variables(COMPILE_OPTIONS)

add_executable(eigen_comparison eigen_comparison.cpp)
target_link_libraries(eigen_comparison PRIVATE slap::slap Eigen::Eigen fmt::fmt)

add_compile_options(-O3)
add_executable(slap_matmul slap_matmul.cpp)
target_link_libraries(slap_matmul PRIVATE slap::slap)

set_target_properties(slap_matmul PROPERTIES COMPILE_FLAGS "-save-temps")

get_target_property(FLAGS slap_matmul COMPILE_OPTIONS)
cmake_print_variables(FLAGS)
