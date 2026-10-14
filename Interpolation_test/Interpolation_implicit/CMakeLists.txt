cmake_minimum_required(VERSION 3.20)

project(Interpolation_implicit LANGUAGES CXX)

add_executable(Interpolation_implicit main.cpp)

set(SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Interpolation-SDK")

target_include_directories(Interpolation_implicit PRIVATE
    "${SDK_DIR}/include"
)

add_library(InterpolationSDK SHARED IMPORTED GLOBAL)

set_target_properties(InterpolationSDK PROPERTIES
    IMPORTED_IMPLIB "${SDK_DIR}/lib/Interpolation.lib"
    IMPORTED_LOCATION "${SDK_DIR}/bin/Interpolation.dll"
)

target_link_libraries(Interpolation_implicit PRIVATE InterpolationSDK)

add_custom_command(TARGET Interpolation_implicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DIR}/bin/Interpolation.dll"
        "$<TARGET_FILE_DIR:Interpolation_implicit>"
)
