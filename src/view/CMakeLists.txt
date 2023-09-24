find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

set(VIEW_SOURCES
        main.cpp
        mainwindow.cpp
        qcustomplot.cpp
        credit_calc.cpp
        deposit_calc.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(view_target STATIC
        MANUAL_FINALIZATION
        ${VIEW_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalc_1_0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(view_target STATIC
            ${VIEW_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_library(view_target STATIC
            ${VIEW_SOURCES}
        )
    endif()
endif()
target_link_libraries(view_target PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(view_target PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_target(view_target)
endif()
