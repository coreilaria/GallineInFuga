#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

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
  Point separation(std::vector<Boid> &);
  Point alignment(std::vector<Boid> &);
  Point cohesion(std::vector<Boid> &);

  // void update(std::vector<Boid> &, std::vector<Boid> &);
  Boid update_boid(std::vector<Boid> &, std::vector<Boid> &);
  static void evolve(std::vector<Boid> &);

  Point border();  // da implementare per decidere il comportamento ai bordi
};

#endif