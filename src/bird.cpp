#include "../include/bird.hpp"

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <memory>
#include <numeric>
#include <vector>

#include "../include/graphic.hpp"
#include "../include/point.hpp"

// Implementation of Bird class
Bird::Bird() = default;
Bird::Bird(Point const& position, Point const& velocity) : position_(position), velocity_(velocity){};

Point Bird::get_position() const { return position_; }
Point Bird::get_velocity() const { return velocity_; }

void Bird::set_position(Point position) { position_ = position; };
void Bird::set_velocity(Point velocity) { velocity_ = velocity; };

void Bird::friction(const double maxSpeed, Point& velocity) {
  if (velocity.module() > maxSpeed) {
    velocity = maxSpeed * (velocity / velocity.module());
  }
};
void Bird::boost(const double minSpeed, Point& velocity) {
  if (velocity.module() < minSpeed) {
    velocity = minSpeed * (velocity / velocity.module());
  }
};
Point Bird::border(const double margin, const double turn_factor, Point v) {
  double v4_x{v.get_x()};
  double v4_y{v.get_y()};

  if (position_.get_x() < graphic_par::statsWidth + margin) {
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

Bird::~Bird(){};

// Implementation of Boid class
// non mi è chiaro perchè io non possa assegnare i valori nella lista
Boid::Boid() : Bird(){};
Boid::Boid(Point const& pos, Point const& vel) : Bird(pos, vel){};

Point Boid::separation(const double s, const double ds, std::vector<std::shared_ptr<Bird>>& near) {
  Point v1{0., 0.};

  for (int i = 0; i < static_cast<int>(near.size()); ++i) {
    Point x1 = near[i]->get_position();

    // We are supposing that the near vector does not contain the current boid,
    // for this reason we implemented the flight rules with near.size() instead of near.size()-1

    if (x1.distance(position_) < ds) {
      v1 += -s * (x1 - position_);
    }
  }
  return v1;  // todo METTERE FOR_EACH
};

Point Boid::alignment(const double a, std::vector<std::shared_ptr<Bird>>& near) {
  Point sum = std::accumulate(near.begin(), near.end(), Point(0., 0.),
                              [](Point acc, std::shared_ptr<Bird> boid) { return acc + boid->get_velocity(); });

  // TODO mettere assert: near_.size() > 1, e che 0 < a < 1

  // Subtracting from the nearest boids' mean velocity the current boid's one
  // and then multiplying for an alignment factor
  return a * (sum / near.size() - velocity_);
};

Point Boid::cohesion(const double c, std::vector<std::shared_ptr<Bird>>& near) {
  // Point sum{0., 0.};

  Point sum = std::accumulate(near.begin(), near.end(), Point(0., 0.),
                              [](Point acc, std::shared_ptr<Bird> boid) { return acc + boid->get_position(); });

  // Subtracting from the nearest boids' center of mass the current boid's
  // position and then multiplying for a cohesion factor

  return c * (sum / near.size() - position_);
  // TODO mettere assert: near_.size() > 1
};

// Implementation of Predator class
Predator::Predator() : Bird(){};
Predator::Predator(Point const& pos, Point const& vel) : Bird(pos, vel){};
Point Predator::separation(const double s, const double ds, std::vector<std::shared_ptr<Bird>>& near) {
  // Point v1{0., 0.};

  Point v1 =
      std::accumulate(near.begin(), near.end(), Point(0., 0.), [this, s, ds](Point acc, std::shared_ptr<Bird> boid) {
        if (boid->get_position().distance(position_) < ds) {
          acc += -s * 0.2 * (boid->get_position() - position_);
        }
        return acc;
      });

  // for (int i = 0; i < static_cast<int>(near.size()); ++i) {
  //   Point x1 = near[i]->get_position();

  //   // We are supposing that the near vector does not contain the current boid,
  //   // for this reason we implemented the flight rules with near.size() instead of near.size()-1

  //   if (x1.distance(position_) < ds) {
  //     v1 += -s * (x1 - position_);
  //   }
  // }
  return v1;
};
