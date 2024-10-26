#include "../include/boid.hpp"

#include <cmath>
#include <numbers>

#include "../include/constants.hpp"
#include "../include/point.hpp"

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel)
    : position_{pos.get_x(), pos.get_y()}, velocity_{vel.get_x(), vel.get_y()} {};

Point Boid::get_position() const { return position_; }
Point Boid::get_velocity() const { return velocity_; }

Point Boid::separation(std::vector<Boid>& near) {
  Point v1{0., 0.};

  // using static_cast to convert from unsign int to int
  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    Point x1 = near[i].get_position();

    // We are supposing that the near vector does not contain the current boid,
    // for this reason we implemented the flight rules with near.size() instead of near.size()-1

    if (x1.distance(position_) < ds) v1 += -s * (x1 - position_);
  }
  return v1;
}

Point Boid::alignment(std::vector<Boid>& near) {
  Point sum{0., 0.};
  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    sum += near[i].get_velocity();
  }
  // TODO mettere assert: near_.size() > 1, e che 0 < a < 1

  // Subtracting from the nearest boids' mean velocity the current boid's one
  // and then multiplying for an alignment factor
  return a * (sum / near.size() - velocity_);
};

Point Boid::cohesion(std::vector<Boid>& near) {
  Point sum{0., 0.};

  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    sum += near[i].get_position();
  }
  // Subtracting from the nearest boids' center of mass the current boid's
  // position and then multiplying for a cohesion factor

  return c * (sum / near.size() - position_);
  // TODO mettere assert: near_.size() > 1
};

// Point Boid::border() {
//   double v4_x{0.};
//   double v4_y{0.};

//   if (std::abs(position_.get_x()) < maxPos - d / 12) {
//     if (position_.get_x() < 0) {
//       v4_x = -b * (minPos - position_.get_x());
//     } else {
//       v4_x = -b * (maxPos - position_.get_x());
//     }
//   }

//   if (std::abs(position_.get_y()) < maxPos - d / 12) {
//     if (position_.get_y() < 0) {
//       v4_y = -b * (minPos - position_.get_y());
//     } else {
//       v4_y = -b * (maxPos - position_.get_y());
//     }
//   }
//   return Point(v4_x, v4_y);
// };

void Boid::friction(Point& velocity) {
  if (velocity.module() > velMax) {
    velocity = velMax * (velocity / velocity.module());
  }
};

Boid Boid::update_boid(std::vector<Boid>& flock_in, std::vector<Boid>& near) {
  // USARE ALGORITMO SE NON USIAMO QUAD-TREE
  Point p, v;
  p = position_;
  v = velocity_;

  // double theta;

  // if (velocity_.get_x() <= 0) {
  //   if (velocity_.get_x() == 0) {
  //     theta = M_PI();
  //   } else {
  //     theta{std::atan(velocity_.get_y() / velocity_.get_x())};
  //   }

  // } else {
  //   theta{std::atan(velocity_.get_y() / velocity_.get_x() +
  //                   M_PI())};  // pensare se c'è un altro modo per inserire il pi greco
  // }

  for (int i = 0; i < static_cast<int>(flock_in.size()); ++i) {
    if (position_.distance(flock_in[i].get_position()) < d && &flock_in[i] != this) {
      near.push_back(flock_in[i]);
    }
  }

  if (near.empty() == false) {
    v += separation(near) + alignment(near) + cohesion(near);
  }
   v = border(v);
  //  friction(v);

  p += dt * v;

  return Boid(p, v);
};

// da sostituire con for_each
void Boid::evolve(std::vector<Boid>& flock_in) {
  std::vector<Boid> flock_out(N);
  for (int i = 0; i < static_cast<int>(flock_in.size()); ++i) {
    std::vector<Boid> near;
    flock_out[i] = flock_in[i].update_boid(flock_in, near);
  }
  flock_in = flock_out;
};

Point Boid::border(Point v) {
  double v4_x{v.get_x()};
  double v4_y{v.get_y()};

  if (position_.get_x() < margin) {
    v4_x += turn_factor;
  }

  if (position_.get_x() > (windowWidth - margin)) {
    v4_x -= turn_factor;
  }

  if (position_.get_y() < margin) {
    v4_y += turn_factor;
  }

  if (position_.get_y() > (windowHeight - margin)) {
    v4_y -= turn_factor;
  }
  return Point(v4_x, v4_y);
};