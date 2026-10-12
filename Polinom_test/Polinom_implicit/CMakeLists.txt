cmake_minimum_required(VERSION 3.20)

project(Polinom_implicit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Polinom-SDK")

add_executable(Polinom_implicit main.cpp)

target_include_directories(Polinom_implicit PRIVATE
    "${SDK_DIR}/include"
)

add_library(Polinom SHARED IMPORTED)

set_target_properties(Polinom PROPERTIES
    IMPORTED_IMPLIB "${SDK_DIR}/lib/Polinom.lib"
    IMPORTED_LOCATION "${SDK_DIR}/bin/Polinom.dll"
)

target_link_libraries(Polinom_implicit PRIVATE Polinom)

add_custom_command(TARGET Polinom_implicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DIR}/bin/Polinom.dll"
        "$<TARGET_FILE_DIR:Polinom_implicit>"
)
