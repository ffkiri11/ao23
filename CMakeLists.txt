cmake_minimum_required(VERSION 3.5)

project(chatroom LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt5 COMPONENTS Widgets Network LinguistTools Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network LinguistTools Quick REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_library(chatroom OBJECT
        chatroom.h
        chatroom.cpp)

add_library(chatroomuser OBJECT
            chatroomuser.h
            chatroomuser.cpp)

add_library(chatroomtcpmiddleware OBJECT
            socketwrapper.h
            socketwrapper.cpp
            chatroomtcpmiddleware.h
            chatroomtcpmiddleware.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chatroom_server
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(chatroom_server SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(chatroom_server
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

#find_package(Qt5 COMPONENTS Quick REQUIRED)

target_link_libraries(chatroom_server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(chatroom_server PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(chatroom PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(chatroomuser PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(chatroomtcpmiddleware PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(chatroom_server PRIVATE chatroom)
target_link_libraries(chatroom_server PRIVATE chatroomtcpmiddleware)
target_link_libraries(chatroom_server PRIVATE chatroomuser)
