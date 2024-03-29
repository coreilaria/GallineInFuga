#ifndef BOID_HPP
#define BOID_HPP

#include <vector>
#include "point.hpp"

class Boid {
 private:
    Point position_;
    Point velocity_;
    static std::vector<Boid*> flock_;

 public:
    Boid();
    Boid(Point const&, Point const&);
    Point separation(double);
    Point alignment(double);
    Point cohesion(double);
    static void addBoid(Point const&, Point const&);
    static void update();



};

#endif