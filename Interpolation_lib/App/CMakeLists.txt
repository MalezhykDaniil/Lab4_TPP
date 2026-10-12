add_executable(InterpolationTest
    main.cpp
)

target_link_libraries(InterpolationTest PRIVATE
    Interpolation
)

add_custom_command(TARGET InterpolationTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Interpolation>
        $<TARGET_FILE_DIR:InterpolationTest>
)