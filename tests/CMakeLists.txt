# Target: pool
add_executable(pool
    pool.cc

    ${PROJECT_SOURCE_DIR}/src/models/pool.cc
)
target_compile_features(pool PUBLIC cxx_std_23)
target_include_directories(pool
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)


# Target: rounding
add_executable(rounding
    rounding.cc
)
target_compile_features(rounding PUBLIC cxx_std_23)


# Target: singleton
add_executable(singleton
    singleton.cc

    ${PROJECT_SOURCE_DIR}/src/models/singleton.cc
)
target_compile_features(singleton PUBLIC cxx_std_23)
target_include_directories(singleton
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)


# Target: stfn
add_executable(stfn
    stfn.cc

    ${PROJECT_SOURCE_DIR}/src/models/singleton.cc
)
target_compile_features(stfn PUBLIC cxx_std_23)
target_include_directories(stfn
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)


# Target: vector
add_executable(vector
    vector.cc

    ${PROJECT_SOURCE_DIR}/src/models/math.cc
)
target_compile_features(vector PUBLIC cxx_std_23)
target_include_directories(vector
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)
