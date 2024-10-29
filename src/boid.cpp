#include "../include/boid.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <numeric>
#include <vector>

#include "../include/namespace.hpp"
#include "../include/point.hpp"

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel)
    : position_{pos.get_x(), pos.get_y()}, velocity_{vel.get_x(), vel.get_y()} {};

Point Boid::get_position() const { return position_; }
Point Boid::get_velocity() const { return velocity_; }

Point Boid::separation(const double s, const double ds, std::vector<Boid*>& near) {
  Point v1{0., 0.};

  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    Point x1 = near[i]->get_position();

    // We are supposing that the near vector does not contain the current boid,
    // for this reason we implemented the flight rules with near.size() instead of near.size()-1

    // if (x1.distance(position_) < ds) {
    //   if (x1.distance(position_) < (ds /2)) {
    //     v1 += -s * (x1 - position_);
    //   } else {
    //     v1 += -s * ((x1 - position_) / (x1 - position_).module());
    //   }
    // }

    if (x1.distance(position_) < ds) {
      v1 += -s * (x1 - position_);
    }
  }
  return v1;
};

Point Boid::alignment(const double a, std::vector<Boid*>& near) {
  Point sum = std::accumulate(near.begin(), near.end(), Point(0., 0.),
                              [](Point acc, Boid* boid) { return acc + boid->get_velocity(); });

  // TODO mettere assert: near_.size() > 1, e che 0 < a < 1

  // Subtracting from the nearest boids' mean velocity the current boid's one
  // and then multiplying for an alignment factor
  return a * (sum / near.size() - velocity_);

  // for (int i = 0; i < static_cast<int>(near.size()); ++i) {
  //   sum += near[i].get_velocity();
};

Point Boid::cohesion(const double c, std::vector<Boid*>& near) {
  // Point sum{0., 0.};

  Point sum = std::accumulate(near.begin(), near.end(), Point(0., 0.),
                              [](Point acc, Boid* boid) { return acc + boid->get_position(); });

  // for (int i = 0; i < static_cast<int>(near.size()); ++i) {
  //   sum += near[i].get_position();
  // }
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

void Boid::friction(const double maxSpeed, Point& velocity) {
  if (velocity.module() > maxSpeed) {
    velocity = maxSpeed * (velocity / velocity.module());
  }
};
void Boid::boost(const double minSpeed, Point& velocity) {
  if (velocity.module() < minSpeed) {
    velocity = minSpeed * (velocity / velocity.module());
  }
};

// da sostituire con for_each

Point Boid::border(const double margin, const double turn_factor, Point v) {
  double v4_x{v.get_x()};
  double v4_y{v.get_y()};

  if (position_.get_x() < margin) {
    v4_x += turn_factor;
  }

  if (position_.get_x() > (graphic_par::windowWidth - margin)) {
    v4_x -= turn_factor;
  }

  if (position_.get_y() < margin) {
    v4_y += turn_factor;
  }

  if (position_.get_y() > (graphic_par::windowHeight - margin)) {
    v4_y -= turn_factor;
  }
  return Point(v4_x, v4_y);
};