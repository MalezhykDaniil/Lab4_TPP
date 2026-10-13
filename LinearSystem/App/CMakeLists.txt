add_executable(LinearSystemApp
    main.cpp
)

target_link_libraries(LinearSystemApp PRIVATE
    LinearSystemLib
)

target_compile_features(LinearSystemApp PRIVATE cxx_std_20)

add_custom_command(TARGET LinearSystemApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:LinearSystemLib>"
        "$<TARGET_FILE_DIR:LinearSystemApp>"
    COMMENT "Copying LinearSystemLib.dll next to LinearSystemApp.exe"
)