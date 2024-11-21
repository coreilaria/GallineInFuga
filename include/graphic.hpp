#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "../include/bird.hpp"

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

sf::VertexArray createTriangle(std::shared_ptr<Bird>&);
void rotateTriangle(std::shared_ptr<Bird>& bird, sf::VertexArray&, double);

}  // namespace triangles

#endif

// cmake -S ./ -B build -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
