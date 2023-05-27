cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(file_association_manager VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
  src/main.cpp
  src/fileassociationmanagerwidget.cpp
  src/fileassociationmanagerwidget.h
  src/filedatahelpers.cpp
  src/filedatahelpers.h
  src/record.h
  src/recordstablemodel.h
  src/recordstablemodel.cpp
  src/recordstableview.h
  src/recordstableview.cpp
  assets/resources.qrc
)

add_subdirectory(libs/csv_parser)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(file_association_manager PRIVATE Qt5::Widgets csv_parser)

if(WIN32)
    find_library(SHLWAPI Shlwapi.lib REQUIRED)
    target_link_libraries(file_association_manager PRIVATE ${SHLWAPI})
endif()
