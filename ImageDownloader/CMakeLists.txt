cmake_minimum_required(VERSION 3.5)

project(ImageDownloader LANGUAGES CXX)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:/Qt/6.3.1/msvc2019_64)
elseif(!WIN32)
    set(CMAKE_PREFIX_PATH ~/Qt6.3.1/6.3.1/gcc_64)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG RELEASE)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Errors/Error.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPSocket/TCPSocket.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request/Request.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Browser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Image.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Downloader/Downloader.h
)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Errors/Error.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPSocket/TCPSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Browser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Downloader/Downloader.cpp
)

set(qml_qrc ${CMAKE_CURRENT_SOURCE_DIR}/data/qml.qrc)

add_library(mainlib
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_sources(mainlib
    PRIVATE 
        ${SOURCE_FILES}
    PUBLIC
        ${HEADER_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        )   

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets Qml Gui Network Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Qml Gui Network Multimedia REQUIRED)

add_definitions(-DQT_NO_KEYWORDS)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${qml_qrc})

target_link_libraries(mainlib
                        PUBLIC
                        Qt${QT_VERSION_MAJOR}::Core 
                        Qt${QT_VERSION_MAJOR}::Quick 
                        Qt${QT_VERSION_MAJOR}::Widgets
                        Qt${QT_VERSION_MAJOR}::Qml
                        Qt${QT_VERSION_MAJOR}::Gui
                        Qt${QT_VERSION_MAJOR}::Network
                        Qt${QT_VERSION_MAJOR}::Multimedia
)

target_link_libraries(${PROJECT_NAME} PUBLIC mainlib)
