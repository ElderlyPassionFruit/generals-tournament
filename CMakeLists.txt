cmake_minimum_required(VERSION 3.9)

project(generals-tournament)

set (CMAKE_CXX_STANDARD 17)

set(PROJECT_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(PROJECT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set(PROJECT_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)


add_subdirectory(${PROJECT_SOURCES_DIR})
add_subdirectory(${PROJECT_EXAMPLES_DIR})