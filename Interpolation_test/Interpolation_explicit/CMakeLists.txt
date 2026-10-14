cmake_minimum_required(VERSION 3.20)

project(Interpolation_explisit LANGUAGES CXX)

add_executable(Interpolation_explisit main.cpp)

set(SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Interpolation-SDK")



add_custom_command(TARGET Interpolation_explisit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DIR}/bin/Interpolation.dll"
        "$<TARGET_FILE_DIR:Interpolation_explisit>"
)