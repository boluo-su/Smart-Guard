cmake_minimum_required(VERSION 3.5)
project(video-monitor-client)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(src)
include_directories(${CMAKE_SOURCE_DIR}/third_party)

file(GLOB SOURCES
    src/main.cpp
    src/ui/*.cpp
    src/device/*.cpp
    src/network/*.cpp
    src/video/*.cpp
    src/history/*.cpp
    src/utils/*.cpp
    src/receiver/*.cpp
)

add_executable(video-monitor-client ${SOURCES})

target_link_libraries(video-monitor-client Qt5::Widgets ${OpenCV_LIBS})

