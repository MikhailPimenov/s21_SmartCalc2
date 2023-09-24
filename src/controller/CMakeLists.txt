set(CONTROLLER_SOURCES
    controller.cc
)
add_library(controller_target ${CONTROLLER_SOURCES})

set_source_files_properties(${CONTROLLER_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)