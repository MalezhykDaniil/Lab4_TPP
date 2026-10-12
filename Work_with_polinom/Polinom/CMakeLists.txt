
add_library(Polinom SHARED
    src/Polinom.cpp
)

target_include_directories(Polinom
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Polinom PUBLIC cxx_std_17)


target_compile_definitions(Polinom PRIVATE POLINOM_EXPORTS)
