cmake_minimum_required(VERSION 3.20)

project(Polinom_explicit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Polinom-SDK")

add_executable(Polinom_explicit main.cpp)

add_custom_command(TARGET Polinom_explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DIR}/bin/Polinom.dll"
        "$<TARGET_FILE_DIR:Polinom_explicit>"
)
