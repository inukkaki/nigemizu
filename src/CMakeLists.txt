# Modify the location of the executable output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})


# Target: nigemizu
add_executable(nigemizu
    main.cc

    controllers/loop.cc

    core/pool.cc
    core/singleton.cc

    entity/base.cc
    entity/delegate.cc
    entity/entity.cc
    entity/playable.cc

    interfaces/framerate.cc
    interfaces/keyboard.cc
    interfaces/texture.cc

    meta/assert.cc
    meta/boot.cc
    meta/modal.cc
    meta/winfunc.cc

    models/config.cc
    models/math.cc
    models/timer.cc
)
target_compile_features(nigemizu PUBLIC cxx_std_23)
target_include_directories(nigemizu
    PUBLIC
        ${PATH_TO_SDL2}/include
        ${PROJECT_SOURCE_DIR}/src
)
target_link_directories(nigemizu PUBLIC ${PATH_TO_SDL2}/lib)
target_link_libraries(nigemizu PUBLIC ${SDL2_LIBS})
