set(CALCULATOR_SOURCES
    calculator.cc
    expressionToTokens.cc
)
add_library(calculator_target ${CALCULATOR_SOURCES})

set_source_files_properties(${CALCULATOR_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)