set(CONTROLLER_SOURCES
    controller.cc
)
add_library(controller_target STATIC ${CONTROLLER_SOURCES})

set_source_files_properties(${CONTROLLER_SOURCES} PROPERTIES LANGUAGE CXX)