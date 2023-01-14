# Set documentation output directory
set(PROJECT_DOC_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/docs/_build)

# Create a Doxyfile from the template, populating the content with CMake variables
set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/docs/Doxyfile)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

# Add documentation target
add_custom_target(doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Build documentation with Doxygen." )