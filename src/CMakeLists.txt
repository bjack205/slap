if (SLAP_CLANG_TIDY AND (CMAKE_C_COMPILER_ID STREQUAL "Clang")) 
  message(STATUS "Running clang-tidy on source directory.")
  set(CMAKE_C_CLANG_TIDY
    clang-tidy;
    -export-fixes=tidy-fixes.yaml;
    -header-filter=.;
    --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy;
    # -extra-arg="--std=c11";
    # -checks="bugprone-*, clang-*, google-*, readability-*, modernize-*, performance-*, portability-*";
  )
endif()

add_subdirectory(slap)