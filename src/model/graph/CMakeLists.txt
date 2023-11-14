set(GRAPH_SOURCES
    graphCalculator.cc
)
add_library(graph_target ${GRAPH_SOURCES})

set_source_files_properties(${GRAPH_SOURCES} PROPERTIES LANGUAGE CXX)
add_compile_options(-g)