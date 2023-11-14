cmake_minimum_required(VERSION 3.5)

project(SmartCalc_2_0 VERSION 0.1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON) 
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: do it in CMakeLists.txt for view but not here
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

set(PROJECT_SOURCES
    entry_point.cc
)
add_compile_options(-g)

# include_directories(${PROJECT_SOURCE_DIR}/model)
# link_directories(${PROJECT_SOURCE_DIR}/model)
# add_subdirectory(${PROJECT_SOURCE_DIR}/model)

include_directories(${PROJECT_SOURCE_DIR}/view)
link_directories(${PROJECT_SOURCE_DIR}/view)
add_subdirectory(${PROJECT_SOURCE_DIR}/view)

# include_directories(${PROJECT_SOURCE_DIR}/controller)
# link_directories(${PROJECT_SOURCE_DIR}/controller)
# add_subdirectory(${PROJECT_SOURCE_DIR}/controller)

include_directories(${PROJECT_SOURCE_DIR}/model/calculator)
link_directories(${PROJECT_SOURCE_DIR}/model/calculator)
add_subdirectory(${PROJECT_SOURCE_DIR}/model/calculator)

include_directories(${PROJECT_SOURCE_DIR}/model/credit)
link_directories(${PROJECT_SOURCE_DIR}/model/credit)
add_subdirectory(${PROJECT_SOURCE_DIR}/model/credit)

include_directories(${PROJECT_SOURCE_DIR}/model/deposit)
link_directories(${PROJECT_SOURCE_DIR}/model/deposit)
add_subdirectory(${PROJECT_SOURCE_DIR}/model/deposit)

include_directories(${PROJECT_SOURCE_DIR}/model/graph)
link_directories(${PROJECT_SOURCE_DIR}/model/graph)
add_subdirectory(${PROJECT_SOURCE_DIR}/model/graph)

include_directories(${PROJECT_SOURCE_DIR}/model/parcer)
link_directories(${PROJECT_SOURCE_DIR}/model/parcer)
add_subdirectory(${PROJECT_SOURCE_DIR}/model/parcer)

include_directories(${PROJECT_SOURCE_DIR}/model/rpn)
link_directories(${PROJECT_SOURCE_DIR}/model/rpn)
add_subdirectory(${PROJECT_SOURCE_DIR}/model/rpn)

# TODO: do it in CMakeLists.txt for view but not here
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
qt_add_executable(SmartCalc_2_0
MANUAL_FINALIZATION
${PROJECT_SOURCES}
)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalc_2_0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
if(ANDROID)
add_library(SmartCalc_2_0 SHARED
${PROJECT_SOURCES}
)
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
add_executable(SmartCalc_2_0
${PROJECT_SOURCES}
)
endif()
endif()
# add_executable(SmartCalc_2_0 ${PROJECT_SOURCES})
target_link_libraries(SmartCalc_2_0 PUBLIC calculator_target)
target_link_libraries(SmartCalc_2_0 PUBLIC credit_target)
target_link_libraries(SmartCalc_2_0 PUBLIC deposit_target)
target_link_libraries(SmartCalc_2_0 PUBLIC graph_target)
target_link_libraries(SmartCalc_2_0 PUBLIC parcer_target)
target_link_libraries(SmartCalc_2_0 PUBLIC rpn_target)
target_link_libraries(SmartCalc_2_0 PUBLIC view_target)


set_target_properties(SmartCalc_2_0 PROPERTIES
MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
MACOSX_BUNDLE TRUE
WIN32_EXECUTABLE TRUE
)

