add_library(slap
    matrix.h
    matrix.c

    linalg.h
    linalg.c
)
target_include_directories(slap INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:"include">
)

add_target_to_install(slap)