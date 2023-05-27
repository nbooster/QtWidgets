cmake_minimum_required(VERSION 3.18)

project(digital-signal-viewer VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/digitalsignalviewerwidget.h
        src/digitalsignalviewerwidget.cpp
        src/digitalsignal.h
        src/digitalsignal.cpp
        src/customqwtplot.h
        src/customqwtplot.cpp
        src/customqwtplotpanner.h
        src/customqwtplotpanner.cpp
        src/customqwtmagnifier.h
        src/customqwtmagnifier.cpp
        src/customqwtscaledraw.h
        src/customqwtscaledraw.cpp
        src/scrollareawidget.h
        src/scrollareawidget.cpp
        src/legendwidget.h
        src/legendwidget.cpp
        src/legendlabel.h
        src/legendlabel.cpp
        src/syncer.h
        src/syncer.cpp
)

add_subdirectory(libs/qwt)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(digital-signal-viewer PRIVATE Qt5::Widgets Qt5::Core qwt)

set_target_properties(digital-signal-viewer PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS digital-signal-viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


