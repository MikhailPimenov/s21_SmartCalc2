set(MODEL_SOURCES
    stack.cc
    parcer.cc
    shunting_yard.cc
    bonus_part.cc
    calc_rpn.cc
    main_c.cc
)
add_library(model_target ${MODEL_SOURCES})

set_source_files_properties(${MODEL_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)