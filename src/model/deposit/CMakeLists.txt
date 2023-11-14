set(DEPOSIT_SOURCES
    depositCalculator.cc
)
add_library(deposit_target ${DEPOSIT_SOURCES})

set_source_files_properties(${DEPOSIT_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)