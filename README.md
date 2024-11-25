# nigemizu

Working in progress...


## How to build the program

This project uses CMake to make a buildsystem.

The directory structure is as follows:
-   `build/` - A build directory. This is to be created by running the CMake
    commands mentioned later.
-   `src/` - A source directory.

First of all, generate a buildsystem by specifying both the source and build
directories:
```
cmake -G Ninja -S . -B build
```

This project uses SDL2 to make a GUI application. Make sure to set
`PATH_TO_SDL2` to the path to a directory that contains SDL2 libraries before
building this:
```
cmake build -DPATH_TO_SDL2=/path/to/SDL2
```

To make an executable, run the following command:
```
cmake --build build
```

The executable is generated in the project directory.

To execute the output, make sure to locate the following shared libraries in
the directory the output sits on:
-   SDL2.dll
-   SDL2_image.dll
