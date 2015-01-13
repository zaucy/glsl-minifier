cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(glsl-minifier)

set(HEADERS
	include/glsl_minifier.h
)

set(SOURCES
	src/minify.cpp
	src/main.cpp
)

include_directories(
	include
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)