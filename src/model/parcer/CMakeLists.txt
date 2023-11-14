set(PARCER_SOURCES
    parcer.cc
    token.cc
    unaryReplacer.cc
    validator.cc
)
add_library(parcer_target ${PARCER_SOURCES})

set_source_files_properties(${PARCER_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)