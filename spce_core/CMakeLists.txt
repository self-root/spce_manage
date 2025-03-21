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
find_package(Qt6 REQUIRED COMPONENTS Network)



add_library(spce_core SHARED
    include/spce_core_global.h
    include/databasemanager.h    src/databasemanager.cpp
    include/shipdao.h            src/shipdao.cpp
    include/ship.h               src/ship.cpp
    include/apicaller.h          src/apicaller.cpp
    include/corecontroller.h     src/corecontroller.cpp
    include/schedulelistmodel.h  src/schedulelistmodel.cpp
    include/schedule.h           src/schedule.cpp
    include/shipdetailmodel.h    src/shipdetailmodel.cpp
    include/flagsvgdownloader.h  src/flagsvgdownloader.cpp
    include/documentformmodel.h  src/documentformmodel.cpp
    include/commissionnairedao.h src/commissionnairedao.cpp
    include/commissionnaire.h    src/commissionnaire.cpp
    include/collecteurdao.h      src/collecteurdao.cpp
    include/collecteur.h         src/collecteur.cpp
    include/basebsdentity.h      src/basebsdentity.cpp
    include/eliminateurdao.h     src/eliminateurdao.cpp
    include/eliminateur.h        src/eliminateur.cpp
    include/dao.h
    include/baseentity.h         src/baseentity.cpp
    include/driver.h             src/driver.cpp
    include/vehicle.h            src/vehicle.cpp
    include/bsd.h                src/bsd.cpp
    include/invoice.h            src/invoice.cpp
    include/mgtoaport.h          src/mgtoaport.cpp
    include/driverdao.h          src/driverdao.cpp
    include/vehicledao.h         src/vehicledao.cpp
    include/bsddao.h             src/bsddao.cpp
    include/invoicedao.h         src/invoicedao.cpp
    include/property_helper.h
    include/baseEntityListModel.h
    include/documentwriter.h     src/documentwriter.cpp
    include/inja.hpp
    include/json.hpp
    include/terminal.h           src/terminal.cpp
    include/terminallistmodel.h  src/terminallistmodel.cpp
    include/shiplistmodel.h      src/shiplistmodel.cpp


)

qt_add_resources(spce_core "templates"
    PREFIX "/templates"
    FILES
        templates/bsd.html
        templates/certificate.html
        templates/invoice.html

)

target_include_directories(spce_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(spce_core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(spce_core PRIVATE SPCE_CORE_LIBRARY)

target_link_libraries(spce_core PRIVATE Qt6::Sql)

target_link_libraries(spce_core PRIVATE Qt6::Network)
