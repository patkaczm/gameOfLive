cmake_minimum_required(VERSION 3.10)
PROJECT(GameOfLive)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/patryk/Qt/5.13.2/gcc_64/")

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)


AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_LIST_DIR}/src sources)
add_library(${PROJECT_NAME}_lib ${sources})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(${PROJECT_NAME}_lib Qt5::Widgets Qt5::Core)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core ${PROJECT_NAME}_lib)

