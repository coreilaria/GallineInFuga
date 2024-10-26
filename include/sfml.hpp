#ifndef SFML_HPP
#define SFML_HPP

#include <SFML/Graphics.hpp>

#include "../include/boid.hpp"
#include "../include/constants.hpp"
#include "../include/point.hpp"

namespace graphic_par {
    const double dt = 0.35;

    const double maxPos = 300.;
    const double minPos = -maxPos;
    const double maxVel = 10.;
    const double minVel = -maxVel;

    const double velMax = 50;
    const float windowWidth = 1200.f;
    const float windowHeight = 900.f;

}  // namespace graphic_par

void toSfmlCoord(sf::Vertex &vertex);



// cmake -S ./ -B build/debug -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
#endif