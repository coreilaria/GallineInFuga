cmake_minimum_required(VERSION 3.22)
project(GallineInFuga)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# Sanitizer
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")


find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(GallineInFuga
    main.cpp
        boids.cpp
        point.cpp
        simulation.cpp
)

target_include_directories(GallineInFuga PRIVATE include)
target_link_libraries(GallineInFuga sfml-graphics)