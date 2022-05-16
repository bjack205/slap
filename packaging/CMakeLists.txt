include(CMakePackageConfigHelpers)

# Install targets
install(EXPORT ${CMAKE_PROJECT_NAME}_export
  DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
  NAMESPACE ${CMAKE_PROJECT_NAME}::
  FILE ${CMAKE_PROJECT_NAME}.cmake
  COMPONENT ${CMAKE_PROJECT_NAME}
)

# Install header files
# Keeps the same folder structure as the src/ directory
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/src/   # final backslash copies contents of src/, not src/ itself
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}  # places all header files under a directory with the project name
    FILES_MATCHING
    PATTERN "*.h"
)

# Write config and version file
install(FILES ${CMAKE_PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
)
