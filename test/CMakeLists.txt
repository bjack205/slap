# function add_ulqr_test(name)
#
# Adds a new executable test called <name>_test.
# Assumes thes source code is in a file called <name>_test.
function (add_slap_test name)
  set(TEST_NAME ${name}_test)
  add_executable(${TEST_NAME}
    ${TEST_NAME}.cpp
  )
  target_link_libraries(${TEST_NAME}
    PRIVATE 
    slap
    gtest_main
    m  # math library
  )
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

## Build the testing library
#add_library(simpletest
#  simpletest/simpletest.h
#  simpletest/simpletest.c
#)
#target_include_directories(simpletest
#  PRIVATE
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
#)

# Add tests
add_slap_test(matrix)
#add_slap_test(linalg)
#add_slap_test(submatrix)