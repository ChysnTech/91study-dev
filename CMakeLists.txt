cmake_minimum_required(VERSION 3.16)
project(91study VERSION 0.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(91study
    src/main.cpp
    src/MainWindow.cpp
)

target_link_libraries(91study Qt6::Core Qt6::Widgets)