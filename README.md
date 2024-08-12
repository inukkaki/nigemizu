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

To make an executable, run the following command:
```
cmake --build build
```

The executable is generated in the project directory.
