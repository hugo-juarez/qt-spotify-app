cmake_minimum_required(VERSION 3.16)

project(qt_spotify_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebSockets)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appqt_spotify_app
    main.cpp
)

qt_add_qml_module(appqt_spotify_app
    URI qt_spotify_app
    QML_FILES
        qml/Main.qml
        qml/ProgressBar.qml
    SOURCES
        backend/backend.h backend/backend.cpp
        backend/playertracker.h backend/playertracker.cpp
    RESOURCES
        assets/icons/next.svg
        assets/icons/pause.svg
        assets/icons/play.svg
        assets/icons/previous.svg
        assets/icons/repeat.svg
        assets/icons/repeat_one.svg
        assets/icons/shuffle.svg
)

target_include_directories(appqt_spotify_app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqt_spotify_app PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt_spotify_app
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqt_spotify_app
    PRIVATE
        Qt6::Quick
        Qt6::WebSockets
)

install(TARGETS appqt_spotify_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
