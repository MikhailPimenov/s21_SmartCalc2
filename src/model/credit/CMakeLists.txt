set(CREDIT_SOURCES
    creditCalculator.cc
)
add_library(credit_target ${CREDIT_SOURCES})

set_source_files_properties(${CREDIT_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)