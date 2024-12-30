#include "../include/bird.hpp"

#include <cassert>
#include <cmath>
#include <memory>
#include <numeric>
#include <vector>

#include "../include/graphic.hpp"
#include "../include/point.hpp"
// Implementation of Bird class
// Bird::Bird() {};
Bird::Bird(Point const& position, Point const& velocity) : position_(position), velocity_(velocity), sightAngle_(0.) {};

Point Bird::get_position() const { return position_; }
Point Bird::get_velocity() const { return velocity_; }

void Bird::set_bird(const Point position, const Point velocity) {
  position_ = position;
  velocity_ = velocity;
};
// void Bird::set_velocity(const Point velocity) { velocity_ = velocity; };

Point Bird::separation(const double s, const double ds, std::vector<std::shared_ptr<Bird>>& near) {
  assert(s > 0 && s < 1);
  assert(ds > 0);
  const Point sum = std::accumulate(near.begin(), near.end(), Point(0., 0.),
                                    [this, ds](Point acc, const std::shared_ptr<Bird>& boid) {
                                      if (boid->get_position().distance(position_) < ds) {
                                        acc += boid->get_position() - position_;
                                      }
                                      return acc;
                                    });
  return (-s) * sum;
};

Point Bird::border(const double margin, const double turn_factor, const Point v) {
  assert(margin > 0 && margin < graphic_par::statsWidth && margin <= graphic_par::windowHeight);
  assert(turn_factor > 0);

  double v4_x{v.get_x()};
  double v4_y{v.get_y()};
  const double giovi{0.5};

  if (position_.get_x() < graphic_par::statsWidth + margin) {
    //   v4_x += std::exp(
    //       (position_.get_x() / (graphic_par::statsWidth + margin) + margin / (margin + graphic_par::statsWidth)) *
    //       turn_factor);
    // v4_x += turn_factor;
    v4_x += turn_factor / std::pow(position_.get_x() - graphic_par::statsWidth, giovi);
  }
  if (position_.get_x() > graphic_par::windowWidth - margin) {
    // v4_x -= std::exp(
    //     (position_.get_x() / (graphic_par::windowWidth - margin) + margin / (margin - graphic_par::statsWidth)) *
    //     turn_factor);
    // v4_x -= turn_factor;
    v4_x -= turn_factor / std::pow(graphic_par::windowWidth - position_.get_x(), giovi);
  }
  if (position_.get_y() < margin) {
    // v4_y += std::exp((position_.get_y() / margin + 1) * turn_factor);
    // v4_y += turn_factor;
  }
  v4_y += turn_factor / std::pow(position_.get_y(), giovi);

  if (position_.get_y() > graphic_par::windowHeight - margin) {
    // v4_y -= std::exp(
    //     (position_.get_y() / (graphic_par::windowHeight - margin) + margin / (margin - graphic_par::windowHeight)) *
    //     turn_factor);
    // v4_y -= turn_factor;
    v4_y -= turn_factor / std::pow(graphic_par::windowHeight - position_.get_y(), giovi);
  }
  return {v4_x, v4_y};
};

Bird::~Bird() = default;

// Implementation of Boid class
Boid::Boid() : Bird() {};
Boid::Boid(Point const& pos, Point const& vel) : Bird(pos, vel) { sightAngle_ = 2. / 3 * M_PI; };

Point Boid::alignment(const double a, std::vector<std::shared_ptr<Bird>>& near_boids) const {
  assert(a > 0 && a < 1);
  const Point sum =
      std::accumulate(near_boids.begin(), near_boids.end(), Point(0., 0.),
                      [](const Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->get_velocity(); });
  return a * (sum / static_cast<double>(near_boids.size()) - velocity_);
};

Point Boid::cohesion(const double c, std::vector<std::shared_ptr<Bird>>& near) const {
  assert(c > 0);
  const Point sum =
      std::accumulate(near.begin(), near.end(), Point(0., 0.),
                      [](const Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->get_position(); });
  return c * (sum / static_cast<double>(near.size()) - position_);
};

Point Boid::repel(const double s, std::vector<std::shared_ptr<Bird>>& near) const {
  assert(s > 0);
  const Point sum = std::accumulate(
      near.begin(), near.end(), Point(0., 0.),
      [this](Point acc, const std::shared_ptr<Bird>& boid) { return acc += boid->get_position() - position_; });
  return (-s * 6) * sum;
}

void Boid::friction(const double maxSpeed[2], Point& velocity) {
  assert(velocity.module() != 0);
  assert(maxSpeed[0] > 0);
  if (velocity.module() > maxSpeed[0]) {
    velocity = maxSpeed[0] * (velocity / velocity.module());
  }
};

void Boid::boost(const double minSpeed[2], Point& velocity) {
  assert(velocity.module() != 0);
  assert(minSpeed[0] > 0);

  if (velocity.module() < minSpeed[0]) {
    velocity = minSpeed[0] * (velocity / velocity.module());
  }
};

// Implementation of Predator class
Predator::Predator() : Bird() {};
Predator::Predator(Point const& pos, Point const& vel) : Bird(pos, vel) { sightAngle_ = 1. / 2 * M_PI; };

Point Predator::chase(const double c, std::vector<std::shared_ptr<Bird>>& near_boids) const {
  assert(c > 0);
  const Point sum =
      std::accumulate(near_boids.begin(), near_boids.end(), Point(0., 0.),
                      [](const Point acc, const std::shared_ptr<Bird>& boid) { return acc + boid->get_position(); });

  return c * 2 * (sum / static_cast<double>(near_boids.size()) - position_);
};
void Predator::friction(const double maxSpeed[2], Point& velocity) {
  assert(maxSpeed[1] > 0);
  assert(velocity.module() != 0);
  if (velocity.module() > maxSpeed[1]) {
    velocity = maxSpeed[1] * (velocity / velocity.module());
  }
};
void Predator::boost(const double minSpeed[2], Point& velocity) {
  assert(velocity.module() != 0);
  assert(minSpeed[1] > 0);
  if (velocity.module() < minSpeed[1]) {
    velocity = minSpeed[1] * (velocity / velocity.module());
  }
};
