#include "boid.hpp"

#include <iostream>

#include "constants.hpp"
#include "point.hpp"

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel)
    : position_{pos.get_x(), pos.get_y()}, velocity_{vel.get_x(), vel.get_y()} {};

// void Boid::set_separation(double ds) {
//   d_separation_ = ds;
// };  // TODO  mettere assert: ds < d, assert

// void Boid::set_distance(double d) { distance_ = d; };

Point Boid::get_position() { return position_; }
const Point Boid::get_velocity() { return velocity_; }
const

    Point
    Boid::separation(std::vector<Boid> near) {
  Point v1{0., 0.};

  // using static_cast to convert from unsign int to int
  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    Point x1 = near[i].get_position();

    // We are supposing that the near vector does not contain the current boid,
    // for this reason we implemented the flight rules with near.size() instead of near.size()-1

    if (x1.distance(position_) < ds) v1 += -s * (x1 - position_);  // chissà se funziona l'operatore +=
  }
  return v1;
}

Point Boid::alignment(std::vector<Boid> near) {
  Point sum{0., 0.};
  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    sum += near[i].get_velocity();  // chissà se funziona l'operatore +=
  }
  // TODO mettere assert: near_.size() > 1, e che 0 < a < 1

  // Subtracting from the nearest boids' mean velocity the current boid's one
  // and then multiplying for an alignment factor
  return a * (sum / near.size() - velocity_);
};

Point Boid::cohesion(std::vector<Boid> near) {
  Point sum{0., 0.};

  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    sum += near[i].get_position();  // chissà se funziona l'operatore +=
  }
  // Subtracting from the nearest boids' center of mass the current boid's
  // position and then multiplying for a cohesion factor

  return c * (sum / near.size() - position_);
  // TODO mettere assert: near_.size() > 1
};

void Boid::update(std::vector<Boid> flock, std::vector<Boid> near) {
  // USARE ALGORITMO SE NON USIAMO QUAD-TREE
  for (int i = 0; i < static_cast<int>(flock.size()); ++i) {
    std::cout << "this: " << this << '\n';
    std::cout << "&flock" << &flock[i] << '\n';

    if (position_.distance(flock[i].get_position()) < d) {
      std::cout << "sono nell'if uno, vicini" << '\n';
      std::cout << "sono nell'if uno, vicini" << '\n';
      std::cout << "sono nell'if uno, vicini, indice " << i << '\n';

      if (&flock[i] != this) {
        near.push_back(flock[i]);
        std::cout << '\n' << "size near uno " << near.size();
        std::cout << "sono nell'if uno, vicini, diversi " << '\n';
        std::cout << "sono nell'if uno, vicini, diversi, indice " << i << '\n';
      }
    }
  }

  if (near.empty() == false) {
    std::cout << '\n' << "sono nell'if due" << '\n';
    std::cout << '\n' << "size near due" << near.size();

    velocity_ += separation(near) + alignment(near) + cohesion(near);  // chissà se funziona l'operatore +=
    std::cout << '\n' << "v_x = " << velocity_.get_x();
    std::cout << '\n' << "v_y = " << velocity_.get_y();
  }

  position_ = position_ + dt * velocity_;

  // TODO svuotare vettore near
};

void Boid::border() {};  // da IMPLEMENTARE
