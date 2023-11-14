set(RPN_SOURCES
    calculatorRpn.cc
    flipStack.cc
    shuntingYard.cc
)
add_library(rpn_target ${RPN_SOURCES})

set_source_files_properties(${RPN_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)