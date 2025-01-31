#include "../include/flock.hpp"

#include <SFML/Graphics/VertexArray.hpp>
#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "../include/bird.hpp"
#include "../include/graphic.hpp"
#include "../include/point.hpp"
#include "../include/statistics.hpp"
#include "../include/triangle.hpp"

namespace flock {

Flock::Flock(const int nBoids, const int nPredators)
    : n_boids_(nBoids), n_predators_(nPredators), s_(0.1), a_(0.1), c_(0.004), b_max_speed_(12.), p_max_speed_(8.),
      b_min_speed_(7.), p_min_speed_(5.) {
  b_flock_.reserve(n_boids_);
  p_flock_.reserve(n_predators_);
}

Flock::Flock(const std::vector<std::shared_ptr<bird::Boid>>& boids,
             const std::vector<std::shared_ptr<bird::Predator>>& predators, const double bMaxSpeed,
             const double pMaxSpeed, const double bMinSpeed, const double pMinSpeed)
    : n_boids_(static_cast<int>(boids.size())), n_predators_(static_cast<int>(predators.size())), b_flock_(boids),
      p_flock_(predators), s_(0.1), a_(0.1), c_(0.004), b_max_speed_(bMaxSpeed), p_max_speed_(pMaxSpeed),
      b_min_speed_(bMinSpeed), p_min_speed_(pMinSpeed) {}

// Flock::Flock(const int nBoids, const int nPredators, const double bMaxSpeed, const double pMaxSpeed,
//              const double bMinSpeed, const double pMinSpeed)
//     : n_boids_(nBoids), n_predators_(nPredators), s_(0.1), a_(0.1), c_(0.004), b_max_speed_(bMaxSpeed),
//     p_max_speed_(pMaxSpeed),
//       b_min_speed_(bMinSpeed), p_min_speed_(pMinSpeed) {
//   b_flock_.reserve(n_boids_);
//   p_flock_.reserve(n_predators_);
// }

int Flock::getBoidsNum() const { return n_boids_; }
int Flock::getPredatorsNum() const { return n_predators_; }
int Flock::getFlockSize() const { return n_predators_ + n_boids_; }
std::vector<std::shared_ptr<bird::Boid>> Flock::getBoidFlock() const { return b_flock_; }
std::vector<std::shared_ptr<bird::Predator>> Flock::getPredatorFlock() const { return p_flock_; }

std::array<double, 2> Flock::getBorderParams() const { return {margin_, turn_factor_}; }

void Flock::setFlockParams() {
  char statement;
  std::cout << "\nWould you like to customize the parameters of the simulation? (Y/n) ";
  std::cin >> statement;

  if (statement == 'Y' || statement == 'y') {
    const double s = graphic_par::getPositiveDouble("\nEnter the separation coefficient: ", std::cin, std::cout);
    const double a = graphic_par::getPositiveDouble("Enter the alignment coefficient: ", std::cin, std::cout);
    const double c = graphic_par::getPositiveDouble("Enter the cohesion coefficient: ", std::cin, std::cout);
    s_ = s;
    a_ = a;
    c_ = c;

  } else if (statement == 'N' || statement == 'n') {
    std::cout << "\nThe simulation parameters are set as default (s = 0.1, a = 0.1, c = 0.004) \n";

  } else {
    std::cerr << "\nInvalid input.";
    std::exit(1);
  }
}

void Flock::generateBirds() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<> dist_pos_x(graphic_par::stats_width, graphic_par::window_width);
  std::uniform_real_distribution<> dist_pos_y(0., graphic_par::window_height);
  std::uniform_real_distribution<> dist_vel_x(graphic_par::min_vel_x, graphic_par::max_vel_x);
  std::uniform_real_distribution<> dist_vel_y(graphic_par::min_vel_y, graphic_par::max_vel_y);

  b_flock_.clear();

  for (int i = 0; i < n_boids_; ++i) {
    b_flock_.emplace_back(std::make_shared<bird::Boid>(point::Point(dist_pos_x(rng), dist_pos_y(rng)),
                                                       point::Point(dist_vel_x(rng), dist_vel_y(rng))));
  }

  if (n_predators_ > 0) {
    p_flock_.clear();
    for (int i = 0; i < n_predators_; ++i) {
      p_flock_.emplace_back(std::make_shared<bird::Predator>(point::Point(dist_pos_x(rng), dist_pos_y(rng)),
                                                             point::Point(dist_vel_x(rng), dist_vel_y(rng))));
    }
    assert(!p_flock_.empty());
  }

  assert(!b_flock_.empty());
}

std::vector<std::shared_ptr<bird::Bird>> Flock::findNearBoids(const int i, const bool is_boid) const {
  // Finds near boids for both boids and predators
  double alpha{};
  double beta{};

  std::vector<std::shared_ptr<bird::Bird>> near_boids;

  for (int j = 0; j < n_boids_; ++j) {
    point::Point other_pos = b_flock_[j]->getPosition();

    if (is_boid) {
      // boid who sees near boids

      beta = b_flock_[i]->getVelocity().angle();
      const point::Point target_pos = b_flock_[i]->getPosition();

      if (i != j && target_pos.distance(other_pos) < d_) {
        alpha = (target_pos - other_pos).angle();

        if (alpha - beta < b_sight_angle_ || alpha - beta > 2 * M_PI - b_sight_angle_) {
          near_boids.emplace_back(b_flock_[j]);
        }
      }
    } else {
      // predator who sees near boids

      beta = p_flock_[i]->getVelocity().angle();
      const point::Point target_pos = p_flock_[i]->getPosition();

      if (target_pos.distance(other_pos) < d_) {
        alpha = (target_pos - other_pos).angle();

        if (alpha - beta < p_sight_angle_ || alpha - beta > 2 * M_PI - p_sight_angle_) {
          near_boids.emplace_back(b_flock_[j]);
        }
      }
    }
  }
  return near_boids;
}

std::vector<std::shared_ptr<bird::Bird>> Flock::findNearPredators(const int i, const bool is_boid) const {
  // Finds near boids for both boids and predators
  double alpha{};
  double beta{};

  std::vector<std::shared_ptr<bird::Bird>> near_predators;

  for (int j = 0; j < n_predators_; ++j) {
    point::Point other_pos = p_flock_[j]->getPosition();

    if (is_boid) {
      // boid who sees near predators

      beta = b_flock_[i]->getVelocity().angle();
      const point::Point target_pos = b_flock_[i]->getPosition();

      if (target_pos.distance(other_pos) < d_) {
        alpha = (target_pos - other_pos).angle();

        if (alpha - beta < b_sight_angle_ || alpha - beta > 2 * M_PI - b_sight_angle_) {
          near_predators.emplace_back(p_flock_[j]);
        }
      }
    } else {
      // predator who sees near predators

      beta = p_flock_[i]->getVelocity().angle();
      const point::Point target_pos = p_flock_[i]->getPosition();

      if (i != j && target_pos.distance(other_pos) < d_) {
        alpha = (target_pos - other_pos).angle();

        if (alpha - beta < p_sight_angle_ || alpha - beta > 2 * M_PI - p_sight_angle_) {
          near_predators.emplace_back(p_flock_[j]);
        }
      }
    }
  }
  return near_predators;
}

std::array<point::Point, 2> Flock::updateBird(sf::VertexArray& triangles, const int i, const bool is_boid) const {
  if (is_boid) {
    point::Point p = b_flock_[i]->getPosition();

    const std::vector<std::shared_ptr<bird::Bird>> near_boids{findNearBoids(i, true)};
    const std::vector<std::shared_ptr<bird::Bird>> near_predators{findNearPredators(i, true)};

    point::Point v = b_flock_[i]->border(margin_, turn_factor_);

    if (!near_predators.empty()) {
      v += b_flock_[i]->repel(s_, near_predators);
    }
    if (!near_boids.empty()) {
      v += b_flock_[i]->separation(s_, ds_, near_boids) + b_flock_[i]->alignment(a_, near_boids) +
           b_flock_[i]->cohesion(c_, near_boids);
    }

    b_flock_[i]->boost(b_min_speed_, v);
    b_flock_[i]->friction(b_max_speed_, v);

    const double theta{v.angle()};
    p += graphic_par::dt * v;

    triangles::rotateTriangle(p, triangles, theta, i, true, n_boids_);
    return {p, v};
  } else {
    point::Point p = p_flock_[i]->getPosition();

    const std::vector<std::shared_ptr<bird::Bird>> near_boids{findNearBoids(i, false)};
    const std::vector<std::shared_ptr<bird::Bird>> near_predators{findNearPredators(i, false)};

    point::Point v = p_flock_[i]->border(margin_, turn_factor_);

    if (!near_predators.empty()) {
      v += p_flock_[i]->separation(s_, d_ * 0.5, near_predators);
    }
    if (!near_boids.empty()) {
      v += p_flock_[i]->chase(c_, near_boids);
    }
    p_flock_[i]->boost(p_min_speed_, v);
    p_flock_[i]->friction(p_max_speed_, v);

    const double theta{v.angle()};
    p += graphic_par::dt * v;

    triangles::rotateTriangle(p, triangles, theta, i, false, n_boids_);
    return {p, v};
  }
}

void Flock::evolve(sf::VertexArray& triangles) const {
  std::vector<point::Point> b_pos;
  std::vector<point::Point> b_vel;

  for (int i = 0; i < n_boids_; ++i) {
    // Evaluates new positions and velocities for each bird::Boid
    std::array<point::Point, 2> p = updateBird(triangles, i, true);
    b_pos.push_back(p[0]);
    b_vel.push_back(p[1]);
  }

  if (n_predators_ > 0) {
    std::vector<point::Point> p_pos;
    std::vector<point::Point> p_vel;

    for (int i = 0; i < n_predators_; ++i) {
      // Evaluates new positions and velocities for each bird::Predator
      std::array<point::Point, 2> p = updateBird(triangles, i, false);
      p_pos.push_back(p[0]);
      p_vel.push_back(p[1]);
    }

    for (int i = 0; i < n_predators_; ++i) {
      // Updates bird::Predator objects' positions and velocities
      p_flock_[i]->setBird(p_pos[i], p_vel[i]);
    }
  }

  for (int i = 0; i < n_boids_; ++i) {
    // Updates bird::Boid objects' positions and velocities
    b_flock_[i]->setBird(b_pos[i], b_vel[i]);
  }
}

statistics::Statistics Flock::statistics() const {
  double meanBoids_dist{0.};
  double meanBoids_dist2{0.};
  double dev_dist{0.};

  if (n_boids_ > 1) {
    for (auto it = b_flock_.begin(); it != b_flock_.begin() + n_boids_; ++it) {
      std::array<double, 2> sum =
          std::accumulate(it, b_flock_.begin() + n_boids_, std::array<double, 2>{0., 0.},
                          [&it](std::array<double, 2>& acc, const std::shared_ptr<bird::Bird>& bird) {
                            acc[0] += (bird->getPosition().distance((*it)->getPosition()));
                            acc[1] += bird->getPosition().distance((*it)->getPosition()) *
                                      bird->getPosition().distance((*it)->getPosition());
                            return acc;
                          });
      meanBoids_dist += sum[0];
      meanBoids_dist2 += sum[1];
    }
    meanBoids_dist /= n_boids_ * (n_boids_ - 1) / 2.;
    meanBoids_dist2 /= n_boids_ * (n_boids_ - 1) / 2.;
    dev_dist = std::sqrt(meanBoids_dist2 - meanBoids_dist * meanBoids_dist);
  }

  double meanBoids_speed{0.};
  double meanBoids_speed2{0.};

  const std::array<double, 2> sum =
      std::accumulate(b_flock_.begin(), b_flock_.begin() + n_boids_, std::array<double, 2>{0., 0.},
                      [](std::array<double, 2>& acc, const std::shared_ptr<bird::Bird>& bird) {
                        acc[0] += bird->getVelocity().module();
                        acc[1] += bird->getVelocity().module() * bird->getVelocity().module();
                        return acc;
                      });
  assert(n_boids_ > 0 && "Flock must contain at least one element");
  meanBoids_speed = sum[0] / n_boids_;
  meanBoids_speed2 = sum[1] / n_boids_;

  const double dev_speed = std::sqrt(meanBoids_speed2 - meanBoids_speed * meanBoids_speed);

  return {meanBoids_dist, dev_dist, meanBoids_speed, dev_speed};
}
}  // namespace flock