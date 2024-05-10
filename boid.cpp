#include "boid.hpp"
#include "point.hpp"

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel)
    : position_{pos.get_x(), pos.get_y()},
      velocity_{vel.get_x(), vel.get_y()} {};

void Boid::set_separation(double ds) {
  d_separation_ = ds;
};  // TODO  mettere assert: ds < d, assert
void Boid::set_distance(double d) { distance_ = d; };

Point Boid::get_position() { return position_; }
const

    Point
    Boid::get_velocity() {
  return velocity_;
}
const

    // Point Boid::separation(double s) {
    //   Point v1{};
    //   Point x1{};

    //   for (int i = 0; i < near_.size(); ++i) {
    //     x1{near_[i]->get_position().get_x(),
    //     near_[i]->get_position().get_y()};
    //     //controllare sintassi costruttore

    //     if (v2.distance(position_) < d_separation_) {
    //       v1{x1.get_x() - position_.get_x(), x1.get_y() - position_.get_y()};
    //       v1 = (1 - s) * v1;
    //     }
    //   }
    //   return v1;
    // };

    Point
    Boid::separation(double s) {
  Point v1{0., 0.};

  // using static_cast to convert from unsign int to int
  for (int i = 0; i < static_cast<int>(near_.size()); ++i) {
    Point x1 = near_[i]->get_position();

    // stiamo supponendo che dentro a near_ non ci sia il boid stesso
    if (x1.distance(position_) < d_separation_)
      v1 += -s * (x1 - position_);  // chissà se funziona l'operatore +=
  }
  return v1;
}

Point Boid::alignment(double a) {
  Point sum{0., 0.};
  for (int i = 0; i < static_cast<int>(near_.size()); ++i) {
    sum += near_[i]->get_velocity();  // chissà se funziona l'operatore +=
  }
  // TODO mettere assert: near_.size() > 1, e che 0 < a < 1

  // Subtracting from the nearest boids' mean velocity the current boid's one
  // and then multiplying for an alignment factor
  return a * (sum / (near_.size() - 1) - velocity_);
};

Point Boid::cohesion(double c) {
  Point sum{0., 0.};

  for (int i = 0; i < static_cast<int>(near_.size()); ++i) {
    sum += near_[i]->get_position();  // chissà se funziona l'operatore +=
  }
  // Subtracting from the nearest boids' center of mass the current boid's
  // position and then multiplying for a cohesion factor
  return c * (sum / (near_.size() - 1) - position_);
  // TODO mettere assert: near_.size() > 1
};

void Boid::addBoid(Point const& p, Point const& v) {
  Boid* b = new Boid(p, v);
  flock_.push_back(b);
  // TODO remember to add destructor for flock vector elements/ delete
};

void Boid::update(double s, double a, double c) {
  velocity_ += separation(s) + alignment(a) +
               cohesion(c);  // chissà se funziona l'operatore +=
  // TODO update position
};

void Boid::border() {};  // da IMPLEMENTARE