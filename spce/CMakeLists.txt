cmake_minimum_required(VERSION 3.16)

project(spce VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup(REQUIRES 6.5)


qt_add_executable(appspce
    main.cpp
    uicontroller.h
    uicontroller.cpp
)

set_source_files_properties(Style.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appspce
    URI spce
    VERSION 1.0
    NO_RESOURCE_TARGET_PATH
    QML_FILES
        "Main.qml"
        "Style.qml"
        "pages/SchedulePage.qml"
        "pages/Invoices.qml"

        "components/MenuButton.qml"
        "components/LineEdit.qml"
        "components/FormSectionTitle.qml"
        "components/MComboBox.qml"
        "components/TextIconBtn.qml"
        "components/MultiLine.qml"
        "components/DateChooser.qml"
)

qt_add_resources(appspce "images"
    PREFIX "/images"
    FILES
        images/spce.png
        images/ship-steering.png
        images/reload.png
        images/invoice_incon1.png
        images/money.png
        images/recycling-truck.png
        images/file-pdf.png
        images/ui-edit.png
        images/ui-delete.png
        images/invoice_hover.png
        images/invoice_normal.png
        images/calendar_normal.png
        images/calendar_hover.png
        images/spce_logo.png
)

qt_add_resources(appspce "fonts"
    PREFIX "/fonts"
    FILES
        fonts/Roboto-Regular.ttf
        fonts/webfont.ttf
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
target_link_libraries(appspce PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS appspce
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
