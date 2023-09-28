set(MODEL_SOURCES
    model.cc
    bonus_model.cc
)
add_library(model_target ${MODEL_SOURCES})

set_source_files_properties(${MODEL_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)