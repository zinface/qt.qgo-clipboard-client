
cmake_minimum_required(VERSION 3.5.1)

project(qgo-clipboard-client LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(NOT DEFINED REMOTE_HOST)
    set(REMOTE_HOST "http://127.0.0.1:9090")
endif(NOT DEFINED REMOTE_HOST)

configure_file(backend/config.h.in config.h @ONLY)

find_package(Qt5 COMPONENTS Core Widgets Network)

# 头文件目录
include_directories()

# 资源文件路径
set(QRC_SOURCES "sources.qrc")

add_executable(${PROJECT_NAME} "main.cpp"
    "mainwindow.cpp" "mainwindow.h" 
    ${QRC_SOURCES}

    backend/clipboardApi.cpp
    backend/clipboardApi.h
    backend/httprequest.cpp
    backend/httprequest.h
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Network)


# include(cmake/linux-install/linux-install.cmake)
