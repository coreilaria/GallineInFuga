cmake_minimum_required(VERSION 3.16)
project(Boids VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# require C++17, without not-standard extensions offered by the compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilitate warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic")

# abilitate address sanitizer and undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(Boids src/point.cpp src/bird.cpp src/flock.cpp src/statistics.cpp src/graphic.cpp src/triangle.cpp src/main.cpp)

target_link_libraries(Boids PRIVATE sfml-graphics)

# if testing enabled...
if (BUILD_TESTING)

    add_executable(Boids.t src/point.cpp src/bird.cpp src/flock.cpp src/statistics.cpp src/graphic.cpp src/triangle.cpp src/test.cpp)

    target_link_libraries(Boids.t PRIVATE sfml-graphics)

    # add executable Boids.t to test lists
    add_test(NAME Boids.t COMMAND Boids.t)

endif ()