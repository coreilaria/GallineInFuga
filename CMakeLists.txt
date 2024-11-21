cmake_minimum_required(VERSION 3.16)
project(Boids VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

find_package(SFML COMPONENTS graphics REQUIRED)
# find_package(TGUI REQUIRED) user interface library

add_executable(Boids src/point.cpp src/bird.cpp src/flock.cpp src/quadtree.cpp src/statistics.cpp src/simulation.cpp src/graphic.cpp) 

target_link_libraries(Boids PRIVATE sfml-graphics)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione

# if (BUILD_TESTING)

#   # aggiungi l'eseguibile Boids.t
#   add_executable(Boids.t src/point.cpp src/boid.cpp src/quadtree.cpp src/test.cpp )

#   target_link_libraries(Boids.t PRIVATE sfml-graphics )

#   # aggiungi l'eseguibile Boids.t alla lista dei test
#   add_test(NAME Boids.t COMMAND Boids.t)


# endif()