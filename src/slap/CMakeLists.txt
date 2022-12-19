if (SLAP_CLANG_TIDY AND (CMAKE_C_COMPILER_ID STREQUAL "Clang"))
  message(STATUS "Running clang-tidy on source directory.")
  set(CMAKE_C_CLANG_TIDY
    clang-tidy;
    -export-fixes=tidy-fixes.yaml;
    -header-filter=.;
    --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy;
    )
endif ()

add_library(slap
  matrix.h
  matrix.c

  errors.h
  errors.c

  matrix_checks.h
  matrix_checks.c

  printing.h
  printing.c

  new_matrix.h
  new_matrix.c
  #    linalg.h
  #    linalg.c
  #
  #    submatrix.h
  #    submatrix.c
  copy_matrix.c copy_matrix.h unary_ops.c unary_ops.h binary_ops.c binary_ops.h)

target_include_directories(slap
  INTERFACE
  $<BUILD_INTERFACE:${slap_SOURCE_DIR}
  $<INSTALL_INTERFACE:"include">
)
