CMAKE_MINIMUM_REQUIRED(VERSION 3.15.3)

project(aye)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

find_package(Threads)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB ${PROJECT_NAME}_SRC
        "main.cpp"
        "ay_reg/src/*.cpp"
        "ay_reg/inc/ay_reg.h"
        "aye/src/*.cpp"
        "aye/inc/aye.h")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
        "aye/inc"
        "ay_reg/inc")

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Network)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
