#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "point.hpp"

class Boid {
 private:
  Point position_;
  Point velocity_;
  double d_separation_;
  double distance_;

  // std::vector<Boid*> flock_;
  // std::vector<Boid*> near_;

 public:
  Boid();
  Boid(Point const&, Point const&);

  void set_separation(double);
  void set_distance(double);

  Point get_position(); const
  Point get_velocity(); const
  Point separation(double, std::vector<Boid>);
  Point alignment(double, std::vector<Boid>);
  Point cohesion(double, std::vector<Boid>);

  static void addBoid(Boid, std::vector<Boid>);
  void update(double, double, double, std::vector<Boid>, std::vector<Boid>);
  void border(); // da implementare per decidere il comportamento ai bordi
};

#endif