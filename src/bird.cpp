#include "../include/bird.hpp"

#include <cassert>
#include <cmath>
#include <memory>
#include <numeric>
#include <vector>

#include "../include/graphic.hpp"
#include "../include/point.hpp"
using namespace point;

namespace bird {

//----------------------------------------------------------------------------------------------------------------------
// ---Implementation of Bird class--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
Bird::Bird(Point const& position, Point const& velocity) : position_(position), velocity_(velocity) {}

Point Bird::getPosition() const { return position_; }
Point Bird::getVelocity() const { return velocity_; }

void Bird::setBird(const Point position, const Point velocity) {
  position_ = position;
  velocity_ = velocity;
}

Point Bird::separation(const double s, const double ds, std::vector<std::shared_ptr<Bird>>& near) {
  assert(s > 0 && s < 1);
  assert(ds > 0);
  const Point sum = std::accumulate(near.begin(), near.end(), Point(0., 0.),
                                    [this, ds](Point acc, const std::shared_ptr<Bird>& boid) {
                                      if (boid->getPosition().distance(position_) < ds) {
                                        acc += boid->getPosition() - position_;
                                      }
                                      return acc;
                                    });
  return (-s) * sum;
}

Point Bird::border(const double margin, const double turn_factor) {
  assert(margin > 0 && margin < graphic_par::statsWidth && margin <= graphic_par::windowHeight);
  assert(turn_factor > 0);

  double v4_x{velocity_.getX()};
  double v4_y{velocity_.getY()};

  if (position_.getX() < graphic_par::statsWidth + margin) {
    v4_x += turn_factor;
  }
  if (position_.getX() > graphic_par::windowWidth - margin) {
    v4_x -= turn_factor;
  }
  if (position_.getY() < margin) {
    v4_y += turn_factor;
  }
  if (position_.getY() > graphic_par::windowHeight - margin) {
    v4_y -= turn_factor;
  }
  return {v4_x, v4_y};
}

Bird::~Bird() = default;

//----------------------------------------------------------------------------------------------------------------------
// ---Implementation of Boid class--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

Boid::Boid() : Bird() {}
Boid::Boid(Point const& pos, Point const& vel) : Bird(pos, vel) { sightAngle_ = 2. / 3 * M_PI; }

Point Boid::alignment(const double a, std::vector<std::shared_ptr<Bird>>& near_boids) const {
  assert(a > 0 && a < 1);
  const Point sum =
      std::accumulate(near_boids.begin(), near_boids.end(), Point(0., 0.),
                      [](const Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->getVelocity(); });
  return a * (sum / static_cast<double>(near_boids.size()) - velocity_);
}

Point Boid::cohesion(const double c, std::vector<std::shared_ptr<Bird>>& near) const {
  assert(c > 0);
  const Point sum =
      std::accumulate(near.begin(), near.end(), Point(0., 0.),
                      [](const Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->getPosition(); });
  return c * (sum / static_cast<double>(near.size()) - position_);
}

Point Boid::repel(const double s, std::vector<std::shared_ptr<Bird>>& near) const {
  assert(s > 0);
  const Point sum = std::accumulate(
      near.begin(), near.end(), Point(0., 0.),
      [this](Point acc, const std::shared_ptr<Bird>& boid) { return acc += boid->getPosition() - position_; });
  return (-s * 6) * sum;
}

void Boid::friction(const double maxSpeed[2], Point& velocity) {
  assert(velocity.module() != 0);
  assert(maxSpeed[0] > 0);
  if (velocity.module() > maxSpeed[0]) {
    velocity = maxSpeed[0] * (velocity / velocity.module());
  }
}

void Boid::boost(const double minSpeed[2], Point& velocity) {
  assert(velocity.module() != 0);
  assert(minSpeed[0] > 0);

  if (velocity.module() < minSpeed[0]) {
    velocity = minSpeed[0] * (velocity / velocity.module());
  }
}

//----------------------------------------------------------------------------------------------------------------------
// ---Implementation of Predator class----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

Predator::Predator() : Bird() {}
Predator::Predator(Point const& pos, Point const& vel) : Bird(pos, vel) { sightAngle_ = 1. / 2 * M_PI; }

Point Predator::chase(const double c, std::vector<std::shared_ptr<Bird>>& near_boids) const {
  assert(c > 0);
  const Point sum =
      std::accumulate(near_boids.begin(), near_boids.end(), Point(0., 0.),
                      [](const Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->getPosition(); });

  return c * 2 * (sum / static_cast<double>(near_boids.size()) - position_);
}
void Predator::friction(const double maxSpeed[2], Point& velocity) {
  assert(maxSpeed[1] > 0);
  assert(velocity.module() != 0);
  if (velocity.module() > maxSpeed[1]) {
    velocity = maxSpeed[1] * (velocity / velocity.module());
  }
}
void Predator::boost(const double minSpeed[2], Point& velocity) {
  assert(velocity.module() != 0);
  assert(minSpeed[1] > 0);
  if (velocity.module() < minSpeed[1]) {
    velocity = minSpeed[1] * (velocity / velocity.module());
  }
}
}  // namespace bird
