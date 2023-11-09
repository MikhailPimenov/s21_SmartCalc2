set(MODEL_SOURCES
    calculator.cc
    calculatorRpn.cc
    creditCalculator.cc
    depositCalculator.cc
    flipStack.cc
    graphCalculator.cc
    parcer.cc
    shuntingYard.cc
    token.cc
    unaryReplacer.cc
    validator.cc
)
add_library(model_target ${MODEL_SOURCES})

set_source_files_properties(${MODEL_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)