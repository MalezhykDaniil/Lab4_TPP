add_library(Interpolation SHARED src/Interpolation.cpp)

target_include_directories(Interpolation
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Interpolation PUBLIC cxx_std_20)

target_compile_definitions(Interpolation PRIVATE INTERPOLATION_EXPORTS)