
add_library(LinearSystemLib SHARED
    src/Linear.cpp
)

target_include_directories(LinearSystemLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(LinearSystemLib
    PRIVATE LINEARSYSTEM_EXPORTS
)

target_compile_features(LinearSystemLib
    PUBLIC cxx_std_20
)

set_target_properties(LinearSystemLib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_SOURCE_DIR}/SDK/bin"

    ARCHIVE_OUTPUT_DIRECTORY
        "${CMAKE_SOURCE_DIR}/SDK/lib"

    LIBRARY_OUTPUT_DIRECTORY
        "${CMAKE_SOURCE_DIR}/SDK/bin"
)
