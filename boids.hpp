#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "point.hpp"

class Boids {
 private:
    Point position_;
    Point velocity_;

 public:
    Point separation();
    Point alignment();
    Point cohesion();
    void update();



};

#endif