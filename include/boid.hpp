#ifndef BOID_HPP
#define BOID_HPP

#include <vector>
#include <algorithm>
#include <numeric>

#include "../include/constants.hpp"
#include "../include/point.hpp"

class Boid {
 private:
  Point position_;
  Point velocity_;

 public:
  Boid();
  Boid(Point const &, Point const &);

  Point get_position() const;
  Point get_velocity() const;
  Point separation(const double, const double, std::vector<Boid *> &);
  Point alignment(const double, std::vector<Boid *> &);
  Point cohesion(const double, std::vector<Boid *> &);

  void friction(const double, Point &);
  Point border(const double, const double, Point);  // da implementare per decidere il comportamento ai bordi
};

#endif