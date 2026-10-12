add_executable(App
    main.cpp
)

target_link_libraries(App PRIVATE Polinom)


add_custom_command(TARGET App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Polinom>
        $<TARGET_FILE_DIR:App>
)

