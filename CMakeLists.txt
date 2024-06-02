cmake_minimum_required(VERSION 3.20)

project(C7H16 C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES "main.c")

add_executable(${PROJECT_NAME} ${SOURCES})