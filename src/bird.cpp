#include "../include/bird.hpp"

#include <cassert>
#include <cmath>
#include <memory>
#include <numeric>
#include <vector>

#include "../include/graphic.hpp"
#include "../include/point.hpp"

namespace bird {

//----------------------------------------------------------------------------------------------------------------------
// ---Implementation of Bird class--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
Bird::Bird(point::Point const& position, point::Point const& velocity) : position_(position), velocity_(velocity) {}

point::Point Bird::getPosition() const { return position_; }
point::Point Bird::getVelocity() const { return velocity_; }

void Bird::setBird(const point::Point position, const point::Point velocity) {
  position_ = position;
  velocity_ = velocity;
}

point::Point Bird::separation(const double s, const double ds, const std::vector<std::shared_ptr<Bird>>& near) const {
  assert(s >= 0 && s <= 1);
  assert(ds > 0);
  const point::Point sum = std::accumulate(near.begin(), near.end(), point::Point(0., 0.),
                                           [this, ds](point::Point acc, const std::shared_ptr<Bird>& boid) {
                                             if (boid->getPosition().distance(position_) < ds) {
                                               acc += boid->getPosition() - position_;
                                             }
                                             return acc;
                                           });
  return (-s) * sum;
}

point::Point Bird::border(const double margin, const double turn_factor) const {
  assert(margin > 0 && margin < graphic_par::stats_width && margin <= graphic_par::window_height);
  assert(turn_factor > 0);

  double v4_x{velocity_.getX()};
  double v4_y{velocity_.getY()};

  if (position_.getX() < graphic_par::stats_width + margin) {
    v4_x += turn_factor;
  }
  if (position_.getX() > graphic_par::window_width - margin) {
    v4_x -= turn_factor;
  }
  if (position_.getY() < margin) {
    v4_y += turn_factor;
  }
  if (position_.getY() > graphic_par::window_height - margin) {
    v4_y -= turn_factor;
  }
  return {v4_x, v4_y};
}

//----------------------------------------------------------------------------------------------------------------------
// ---Implementation of Boid class--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

Boid::Boid() : Bird() {}
Boid::Boid(point::Point const& pos, point::Point const& vel) : Bird(pos, vel) { sight_angle_ = 2. / 3 * M_PI; }

point::Point Boid::alignment(const double a, const std::vector<std::shared_ptr<Bird>>& near) const {
  assert(a >= 0 && a <= 1);
  const point::Point sum = std::accumulate(
      near.begin(), near.end(), point::Point(0., 0.),
      [](const point::Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->getVelocity(); });
  return a * (sum / static_cast<double>(near.size()) - velocity_);
}

point::Point Boid::cohesion(const double c, const std::vector<std::shared_ptr<Bird>>& near) const {
  assert(c >= 0 && c <= 1);
  const point::Point sum = std::accumulate(
      near.begin(), near.end(), point::Point(0., 0.),
      [](const point::Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->getPosition(); });
  return c * (sum / static_cast<double>(near.size()) - position_);
}

point::Point Boid::repel(const double s, const std::vector<std::shared_ptr<Bird>>& near) const {
  assert(s >= 0);
  const point::Point sum = std::accumulate(
      near.begin(), near.end(), point::Point(0., 0.),
      [this](point::Point acc, const std::shared_ptr<Bird>& boid) { return acc += boid->getPosition() - position_; });
  return (-s * 6) * sum;
}

void Boid::friction(const std::array<double, 2>& max_speed, point::Point& velocity) {
  assert(velocity.module() != 0);
  assert(max_speed[0] > 0);
  if (velocity.module() > max_speed[0]) {
    velocity = max_speed[0] * (velocity / velocity.module());
  }
}

void Boid::boost(const std::array<double, 2>& min_speed, point::Point& velocity) {
  assert(velocity.module() != 0);
  assert(min_speed[0] > 0);

  if (velocity.module() < min_speed[0]) {
    velocity = min_speed[0] * (velocity / velocity.module());
  }
}

//----------------------------------------------------------------------------------------------------------------------
// ---Implementation of Predator class----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

Predator::Predator() : Bird() {}
Predator::Predator(point::Point const& pos, point::Point const& vel) : Bird(pos, vel) { sight_angle_ = 1. / 2 * M_PI; }

point::Point Predator::chase(const double c, const std::vector<std::shared_ptr<Bird>>& near_boids) const {
  assert(c >= 0 && c <= 1);
  const point::Point sum = std::accumulate(
      near_boids.begin(), near_boids.end(), point::Point(0., 0.),
      [](const point::Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->getPosition(); });

  return c * 2 * (sum / static_cast<double>(near_boids.size()) - position_);
}
void Predator::friction(const std::array<double, 2>& max_speed, point::Point& velocity) {
  assert(max_speed[1] > 0);
  assert(velocity.module() != 0);
  if (velocity.module() > max_speed[1]) {
    velocity = max_speed[1] * (velocity / velocity.module());
  }
}
void Predator::boost(const std::array<double, 2>& min_speed, point::Point& velocity) {
  assert(velocity.module() != 0);
  assert(min_speed[1] > 0);
  if (velocity.module() < min_speed[1]) {
    velocity = min_speed[1] * (velocity / velocity.module());
  }
}
}  // namespace bird
