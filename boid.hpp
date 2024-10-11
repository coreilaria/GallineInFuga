#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "constants.hpp"
#include "point.hpp"

class Boid {
 private:
  Point position_;
  Point velocity_;
  // double d_separation_ = ds;
  // double distance_ = d;

  // std::vector<Boid*> flock_;
  // std::vector<Boid*> near_;

 public:
  Boid();
  Boid(Point const&, Point const&);

  // void set_separation(double);
  // void set_distance(double);

  Point get_position();
  const Point get_velocity();
  const Point separation(std::vector<Boid>);
  Point alignment(std::vector<Boid>);
  Point cohesion(std::vector<Boid>);

  // static void addBoid(Boid, std::vector<Boid>);
  void update(std::vector<Boid>, std::vector<Boid>);
  void border();  // da implementare per decidere il comportamento ai bordi
};

#endif