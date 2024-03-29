cmake_minimum_required(VERSION 3.5)

project(Skull-King VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        game_logo.h
        game_logo.cpp
        game_logo.ui
        login.cpp
        login.h
        login.ui
        sign_up.cpp
        sign_up.h
        sign_up.ui
        sign_in.cpp
        sign_in.h
        sign_in.ui
        setting.cpp
        setting.h
        setting.ui
        change.h
        change.cpp
        change.ui
        history.cpp
        history.h
        history.ui
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        card.h
        card.cpp
        person.h
        person.cpp
        player.h
        player.cpp
        game.h
        game.cpp
        game.ui
        server.h
        server.cpp
        server.ui
        client.h
        client.cpp
        client.ui
        start.h
        start.cpp
        start.ui
        game_background.qrc
        Sounds.qrc
        customized_button.h
        customized_button.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Skull-King
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Skull-King APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Skull-King SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Skull-King
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Skull-King PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

find_package(Qt6 REQUIRED COMPONENTS Network)
target_link_libraries(Skull-King PRIVATE Qt6::Network)

find_package(Qt6 REQUIRED COMPONENTS Test)
target_link_libraries(Skull-King PRIVATE Qt6::Test)

find_package(Qt6 REQUIRED COMPONENTS Multimedia)
target_link_libraries(Skull-King PRIVATE Qt6::Multimedia)

set_target_properties(Skull-King PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Skull-King
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Skull-King)
endif()
