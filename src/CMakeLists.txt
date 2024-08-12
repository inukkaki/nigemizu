# Modify the location of the executable output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Target: nigemizu
add_executable(nigemizu
    main.cc
)
target_compile_features(nigemizu PUBLIC cxx_std_23)
