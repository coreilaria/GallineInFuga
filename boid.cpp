#include "boid.hpp"
#include "point.hpp"
#include "constants.hpp"

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel)
    : position_{pos.get_x(), pos.get_y()},
      velocity_{vel.get_x(), vel.get_y()} {};

void Boid::set_separation(double ds) {
  d_separation_ = ds;
};  // TODO  mettere assert: ds < d, assert

void Boid::set_distance(double d) { distance_ = d; };

Point Boid::get_position() { return position_; } const

Point Boid::get_velocity() { return velocity_; } const

Point Boid::separation(double s, std::vector<Boid> near) {
  Point v1{0., 0.};

  // using static_cast to convert from unsign int to int
  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    Point x1 = near[i].get_position();

    // stiamo supponendo che dentro a near_ non ci sia il boid stesso
    if (x1.distance(position_) < d_separation_)
      v1 += -s * (x1 - position_);  // chissà se funziona l'operatore +=
  }
  return v1;
}

Point Boid::alignment(double a, std::vector<Boid> near) {
  Point sum{0., 0.};
  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    sum += near[i].get_velocity();  // chissà se funziona l'operatore +=
  }
  // TODO mettere assert: near_.size() > 1, e che 0 < a < 1

  // Subtracting from the nearest boids' mean velocity the current boid's one
  // and then multiplying for an alignment factor
  return a * ((1 / (near.size() - 1)) * sum - velocity_);
};

Point Boid::cohesion(double c, std::vector<Boid> near) {
  Point sum{0., 0.};

  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    sum += near[i].get_position();  // chissà se funziona l'operatore +=
  }
  // Subtracting from the nearest boids' center of mass the current boid's
  // position and then multiplying for a cohesion factor
  return c * ((1 / (near.size() - 1)) * sum  - position_);
  // TODO mettere assert: near_.size() > 1
};

void Boid::addBoid(Boid b, std::vector<Boid> flock) {
  flock.push_back(b);
};

void Boid::update(double s, double a, double c, std::vector<Boid> flock, std::vector<Boid> near) {
  
  for (int i=0; i < static_cast<int>(flock.size()); ++i)
  {
    if (position_.distance(flock[i].get_position()) < distance_)
      near.push_back(flock[i]);
  }
  velocity_ += separation(s, near) + alignment(a, near) +
               cohesion(c, near);  // chissà se funziona l'operatore +=

  position_ = position_ +  dt * velocity_;

  // TODO svuotare vettore near
};


void Boid::border() {};  // da IMPLEMENTARE

//ricordarsi che adesso add boid vuole un boide già formato (nel main)