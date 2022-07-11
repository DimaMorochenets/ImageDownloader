cmake_minimum_required(VERSION 3.5)

project(ImageDownloader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:\\Qt\\6.2.1\\msvc2019_64)
else(!WIN32)
    set(CMAKE_PREFIX_PATH ~/Qt6.3.0)
endif()

set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG RELEASE)

set(qml_qrc ${CMAKE_CURRENT_SOURCE_DIR}/data/qml.qrc)

add_library(mainlib
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Errors/Error.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Errors/Error.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPSocket/TCPSocket.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPSocket/TCPSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request/Request.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Browser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Browser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Image.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Downloader/Downloader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Downloader/Downloader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_sources(mainlib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Errors/Error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPSocket/TCPSocket.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Request/Request.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Browser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Downloader/Downloader.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Errors/Error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPSocket/TCPSocket.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Request/Request.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Browser.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Browser/Image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Downloader/Downloader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)   
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets Qml Gui Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Qml Gui Network REQUIRED)

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
)

target_link_libraries(${PROJECT_NAME} PUBLIC mainlib)

if(WIN32)
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        get_target_property(COREDLL     Qt${QT_VERSION_MAJOR}::Core         IMPORTED_LOCATION_DEBUG)
        get_target_property(QUICKDLL    Qt${QT_VERSION_MAJOR}::Quick        IMPORTED_LOCATION_DEBUG)
        get_target_property(WIDGETDLL   Qt${QT_VERSION_MAJOR}::Widgets      IMPORTED_LOCATION_DEBUG)
        get_target_property(QMLDLL      Qt${QT_VERSION_MAJOR}:Qml           IMPORTED_LOCATION_DEBUG)
        get_target_property(GUIDLL      Qt${QT_VERSION_MAJOR}::Gui          IMPORTED_LOCATION_DEBUG)
        get_target_property(NETWORKDLL  Qt${QT_VERSION_MAJOR}::Network      IMPORTED_LOCATION_DEBUG)
    else(CMAKE_BUILD_TYPE MATCHES Release)
        get_target_property(COREDLL     Qt${QT_VERSION_MAJOR}::Core         IMPORTED_LOCATION_RELEASE)
        get_target_property(QUICKDLL    Qt${QT_VERSION_MAJOR}::Quick        IMPORTED_LOCATION_RELEASE)
        get_target_property(WIDGETDLL   Qt${QT_VERSION_MAJOR}::Widgets      IMPORTED_LOCATION_RELEASE)
        get_target_property(QMLDLL      Qt${QT_VERSION_MAJOR}:Qml           IMPORTED_LOCATION_RELEASE)
        get_target_property(GUIDLL      Qt${QT_VERSION_MAJOR}::Gui          IMPORTED_LOCATION_RELEASE)
        get_target_property(NETWORKDLL  Qt${QT_VERSION_MAJOR}::Network      IMPORTED_LOCATION_RELEASE)
    endif()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${WIDGETDLL} ${COREDLL} ${QUICKDLL} ${GUIDLL} ${NETWORKDLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_PREFIX_PATH}/plugins $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
    )
endif(WIN32)
