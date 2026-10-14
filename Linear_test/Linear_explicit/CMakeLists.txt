cmake_minimum_required(VERSION 3.20)

project(Linear_explicit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Linear-SDK")

add_executable(Linear_explicit main.cpp)

target_include_directories(Linear_explicit PRIVATE
    "${SDK_DIR}/include"
)

add_custom_command(TARGET Linear_explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DIR}/bin/LinearSystemLib.dll"
        "$<TARGET_FILE_DIR:Linear_explicit>"
)