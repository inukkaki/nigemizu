cmake_minimum_required(VERSION 3.28)
project(nigemizu CXX)


# Settings for including SDL2 libraries

set(PATH_TO_SDL2
    CACHE STRING
        "Path to a directory that contains SDL2 libraries."
)

set(SDL2_LIBS)
if(WIN32)
    list(APPEND SDL2_LIBS
        mingw32
        SDL2main
        SDL2
    )
endif()


add_subdirectory(src)
add_subdirectory(tests)
