cmake_minimum_required(VERSION 3.16)

project(spce_core LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Sql)


add_library(spce_core SHARED
    include/spce_core_global.h
  src/databasemanager.cpp
  include/databasemanager.h
  include/shipdao.h
  src/shipdao.cpp
  include/ship.h
  src/ship.cpp
)

target_include_directories(spce_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(spce_core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(spce_core PRIVATE SPCE_CORE_LIBRARY)

target_link_libraries(spce_core PRIVATE Qt6::Sql)
