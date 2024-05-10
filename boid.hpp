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

  static std::vector<Boid*> flock_;
  static std::vector<Boid*> near_;

 public:
  Boid();
  Boid(Point const&, Point const&);

  void set_separation(double);
  void set_distance(double);

  Point get_position(); const
  Point get_velocity(); const
  Point separation(double);
  Point alignment(double);
  Point cohesion(double);

  static void addBoid(Point const&, Point const&);
  void update(double, double, double);
  void border(); // da implementare per decidere il comportamento ai bordi
};

#endif