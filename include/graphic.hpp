#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "../include/bird.hpp"
#include "../include/flock.hpp"

namespace graphic_par {
const double dt = 0.7;

const float windowWidth = 1900.f;
const float windowHeight = 900.f;
const float statsWidth = 0.25 * windowWidth;

const double maxVel_x = 5.;
const double minVel_x = -maxVel_x;

const double maxVel_y = 3;
const double minVel_y = -maxVel_y;
}  // namespace graphic_par

namespace triangles {  // è meglio un unico namespace?

const float baseWidth_ = 7;
const float height_ = 15;

void createTriangles(const Flock& , sf::VertexArray& );
void rotateTriangle(const std::shared_ptr<Bird> & , sf::VertexArray&,  double,  int); // const-qualification of parameters only has an effect in function definitions

}  // namespace triangles

#endif

// cmake -S ./ -B build -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
