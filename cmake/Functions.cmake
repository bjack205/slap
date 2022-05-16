# add_target_to_install(target)
#
# Sets up a target for installation. 
# Creates an alias for the target of the form <project_name>::<target>,
# and adds the target to the export set of the name <project_name>_export
# Sets the OUTPUT_NAME and EXPORT_NAME to be equal to the name of the target.
#
function(add_target_to_install target)

  add_library(${CMAKE_PROJECT_NAME}::${target} ALIAS ${target})
  set_target_properties(${target} PROPERTIES
    OUTPUT_NAME ${target}  # sets the name of the installed library
    EXPORT_NAME ${target}  # sets the name of the imported target
  )
  install(TARGETS ${target}
    EXPORT ${CMAKE_PROJECT_NAME}_export  
  )
  
endfunction()
