# Modify the location of the executable output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})


# Target: nigemizu
add_executable(nigemizu
    main.cc
)
target_compile_features(nigemizu PUBLIC cxx_std_23)
target_include_directories(nigemizu
    PUBLIC
        ${PATH_TO_SDL2}/include
)
target_link_directories(nigemizu PUBLIC ${PATH_TO_SDL2}/lib)
target_link_libraries(nigemizu PUBLIC ${SDL2_LIBS})
