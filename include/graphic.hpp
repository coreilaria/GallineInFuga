#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "../include/bird.hpp"
#include "../include/flock.hpp"

namespace graphic_par {
constexpr double dt = 0.7;

constexpr float windowWidth = 1900.f;
constexpr float windowHeight = 900.f;
constexpr float statsWidth = 0.25 * windowWidth;

constexpr double maxVel_x = 5.;
constexpr double minVel_x = -maxVel_x;

constexpr double maxVel_y = 3;
constexpr double minVel_y = -maxVel_y;
}  // namespace graphic_par

namespace triangles {  // è meglio un unico namespace?

constexpr float baseWidth_ = 7;
constexpr float height_ = 15;

void createTriangles(const Flock& , sf::VertexArray& );
void rotateTriangle(const std::shared_ptr<Bird> & , sf::VertexArray&,  double,  int); // const-qualification of parameters only has an effect in function definitions

}  // namespace triangles

#endif

// cmake -S ./ -B build -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
