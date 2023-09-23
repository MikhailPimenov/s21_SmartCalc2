set(MODEL_SOURCES
    stack.cc
    parcer.cc
    shunting_yard.cc
    bonus_part.cc
    calc_rpn.cc
    main_c.cc
)
add_library(model_target ${MODEL_SOURCES})

# set_source_files_properties(${MODEL_SOURCES} PROPERTIES LANGUAGE CXX)
set_source_files_properties(stack.cc PROPERTIES LANGUAGE CXX)
set_source_files_properties(parcer.cc PROPERTIES LANGUAGE CXX)
set_source_files_properties(shunting_yard.cc PROPERTIES LANGUAGE CXX)
set_source_files_properties(bonus_part.cc PROPERTIES LANGUAGE CXX)
set_source_files_properties(calc_rpn.cc PROPERTIES LANGUAGE CXX)
set_source_files_properties(main_c.cc PROPERTIES LANGUAGE CXX)



set_target_properties(model_target PROPERTIES LANGUAGE CXX)