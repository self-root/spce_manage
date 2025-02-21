cmake_minimum_required(VERSION 3.16)

project(spce VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)


qt_add_executable(appspce
    main.cpp
    uicontroller.h
    uicontroller.cpp
)

qt_add_qml_module(appspce
    URI spce
    VERSION 1.0
    NO_RESOURCE_TARGET_PATH
    QML_FILES
        "Main.qml"
        "pages/SchedulePage.qml"
        "pages/OperationPage.qml"
        "components/MenuButton.qml"
        "components/RotatingIconBtn.qml"

)

qt_add_resources(appspce "images"
    PREFIX "/images"
    FILES
        images/spce.png
        images/icons8-schedule-100.png
        images/icons8-schedule-100-hover.png
        images/ship-steering.png
)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appspce PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appspce
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appspce
    PRIVATE Qt6::Quick
)

target_link_libraries(appspce PRIVATE spce_core)

include(GNUInstallDirs)
install(TARGETS appspce
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
