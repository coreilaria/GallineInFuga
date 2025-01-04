#include "../include/flock.hpp"

#include <SFML/Graphics/VertexArray.hpp>
#include <array>
#include <cassert>
#include <chrono>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "../include/bird.hpp"
#include "../include/graphic.hpp"
#include "../include/point.hpp"
#include "../include/statistics.hpp"

namespace flock {
Flock::Flock()
  : nBoids_(0), nPredators_(0), max_speed_{12., 8.}, min_speed_{7., 5.} {
}

Flock::Flock(const int nBoids, const int nPredators)
  : nBoids_(nBoids), nPredators_(nPredators), max_speed_{12., 8.}, min_speed_{7., 5.} {
  flock_.resize(nBoids_ + nPredators_);
}

int Flock::getBoidsNum() const { return nBoids_; }
int Flock::getPredatorsNum() const { return nPredators_; }
int Flock::getFlockSize() const { return nPredators_ + nBoids_; }
std::vector<std::shared_ptr<bird::Bird>> Flock::getFlock() const { return flock_; }
std::array<double, 2> Flock::getBorderParams() const { return {margin_, turn_factor_}; }

void Flock::setFlock(const std::vector<std::shared_ptr<bird::Bird>>& flock) {
  assert(nBoids_ + nPredators_ == static_cast<int>(flock.size()));
  flock_ = flock;
}

void Flock::setMaxSpeed(const double maxSpeed_b, const double maxSpeed_p) {
  max_speed_[0] = maxSpeed_b;
  max_speed_[1] = maxSpeed_p;
}

void Flock::setMinSpeed(const double minSpeed_b, const double minSpeed_p) {
  min_speed_[0] = minSpeed_b;
  min_speed_[1] = minSpeed_p;
}

void Flock::generateBirds() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist_pos_x(graphic_par::statsWidth, graphic_par::windowWidth);
  std::uniform_real_distribution<double> dist_pos_y(0., graphic_par::windowHeight);
  std::uniform_real_distribution<double> dist_vel_x(graphic_par::minVel_x, graphic_par::maxVel_x);
  std::uniform_real_distribution<double> dist_vel_y(graphic_par::minVel_y, graphic_par::maxVel_y);

  std::vector<bird::Boid> boids;
  std::vector<bird::Predator> predators;

  boids.reserve(nBoids_);
  for (int i = 0; i < nBoids_; ++i) {
    boids.emplace_back(point::Point(dist_pos_x(rng), dist_pos_y(rng)), point::Point(dist_vel_x(rng), dist_vel_y(rng)));
  }
  predators.reserve(nPredators_);
  for (int i = 0; i < nPredators_; ++i) {
    predators.emplace_back(point::Point(dist_pos_x(rng), dist_pos_y(rng)), point::Point(dist_vel_x(rng), dist_vel_y(rng)));
  }

  flock_.clear();

  for (const auto& boid : boids) {
    flock_.push_back(std::make_shared<bird::Boid>(boid));
  }
  for (const auto& predator : predators) {
    flock_.push_back(std::make_shared<bird::Predator>(predator));
  }
  assert(!flock_.empty());
}

std::vector<std::shared_ptr<bird::Bird>> Flock::findNearBoids(const bird::Bird& target, const int i) const {
  // Finds near boids for both boids and predators

  std::vector<std::shared_ptr<bird::Bird>> near;
  const double beta{target.getVelocity().angle()};
  double alpha{};

  for (int j = 0; j < nBoids_; ++j) {
    if (i < nBoids_) {
      // boid who sees near boids
      if (&target != flock_[j].get() && target.getPosition().distance(flock_[j]->getPosition()) < d_) {
        alpha = (target.getPosition() - flock_[j]->getPosition()).angle();

        if (alpha - beta < 2. / 3 * M_PI || alpha - beta > 2 * M_PI - 2. / 3 * M_PI) {
          near.push_back(flock_[j]);
        }
      }
    } else {
      // predator who sees near boids
      if (&target != flock_[j].get() && target.getPosition().distance(flock_[j]->getPosition()) < d_ * 3.5) {
        alpha = (target.getPosition() - flock_[j]->getPosition()).angle();

        if (alpha - beta < 1. / 2 * M_PI || alpha - beta > 2 * M_PI - 1. / 2 * M_PI) {
          near.push_back(flock_[j]);
        }
      }
    }
  }
  return near;
}

std::vector<std::shared_ptr<bird::Bird>> Flock::findNearPredators(const bird::Bird& target, const int i) const {
  // Finds near boids for both boids and predators

  std::vector<std::shared_ptr<bird::Bird>> near;
  const double beta{target.getVelocity().angle()};
  double alpha{};

  for (int j = nBoids_; j < nBoids_ + nPredators_; ++j) {
    if (&target != flock_[j].get() && target.getPosition().distance(flock_[j]->getPosition()) < d_) {
      alpha = (target.getPosition() - flock_[j]->getPosition()).angle();

      if (i < nBoids_) {
        // boid who sees near predators
        if (alpha - beta < 2. / 3 * M_PI || alpha - beta > 2 * M_PI - 2. / 3 * M_PI) {
          near.push_back(flock_[j]);
        }
      } else {
        if (nPredators_ > 1) {
          // predator who sees near predators
          if (alpha - beta < 1. / 2 * M_PI || alpha - beta > 2 * M_PI - 1. / 2 * M_PI) {
            near.push_back(flock_[j]);
          }
        }
      }
    }
  }
  return near;
}

std::array<point::Point, 2> Flock::updateBird(const std::shared_ptr<bird::Bird>& b, sf::VertexArray& triangles, const int i) const {
  point::Point p = b->getPosition();

  const std::vector<std::shared_ptr<bird::Bird>> near_boids{findNearBoids(*b, i)};
  const std::vector<std::shared_ptr<bird::Bird>> near_predators{findNearPredators(*b, i)};

  point::Point v = b->border(margin_, turn_factor_);

  if (i < nBoids_) {
    if (!near_predators.empty()) {
      v += std::dynamic_pointer_cast<bird::Boid>(b)->repel(s_, near_predators);
    }
    if (!near_boids.empty()) {
      v += b->separation(s_, ds_, near_boids) + std::dynamic_pointer_cast<bird::Boid>(b)->alignment(a_, near_boids) +
          std::dynamic_pointer_cast<bird::Boid>(b)->cohesion(c_, near_boids);
    }
  } else {
    if (!near_predators.empty()) {
      v += b->separation(s_ * 0.1, d_ * 0.5, near_predators);
    }
    if (!near_boids.empty()) {
      v += std::dynamic_pointer_cast<bird::Predator>(b)->chase(c_, near_boids);
    }
  }

  b->friction(max_speed_, v);
  b->boost(min_speed_, v);

  const double theta{v.angle()};
  p += graphic_par::dt * v;
  triangles::rotateTriangle(b, triangles, theta, i);
  return {p, v};
}

void Flock::evolve(sf::VertexArray& triangles) const {
  std::vector<point::Point> pos;
  std::vector<point::Point> vel;

  for (int i = 0; i < nBoids_ + nPredators_; ++i) {
    // Aggiorna il bird::Boid esistente e crea un nuovo shared_ptr con il risultato
    std::array<point::Point, 2> p = updateBird(flock_[i], triangles, i);
    pos.push_back(p[0]);
    vel.push_back(p[1]);
  }
  for (int i = 0; i < nBoids_ + nPredators_; ++i) {
    flock_[i]->setBird(pos[i], vel[i]);
  }
}

statistics::Statistics Flock::statistics() const {
  double meanBoids_dist{0.};
  double meanBoids_dist2{0.};
  double dev_dist{0.};

  if (nBoids_ > 1) {
    for (auto it = flock_.begin(); it != flock_.begin() + nBoids_; ++it) {
      std::array<double, 2> sum = std::accumulate(it, flock_.begin() + nBoids_, std::array<double, 2>{0., 0.},
                                                  [&it](std::array<double, 2>& acc, const std::shared_ptr<bird::Bird>& bird) {
                                                    acc[0] += (bird->getPosition().distance((*it)->getPosition()));
                                                    acc[1] += bird->getPosition().distance((*it)->getPosition()) *
                                                        bird->getPosition().distance((*it)->getPosition());
                                                    return acc;
                                                  });
      meanBoids_dist += sum[0];
      meanBoids_dist2 += sum[1];
    }
    meanBoids_dist /= nBoids_ * (nBoids_ - 1) / 2.;
    meanBoids_dist2 /= nBoids_ * (nBoids_ - 1) / 2.;
    dev_dist = std::sqrt(meanBoids_dist2 - meanBoids_dist * meanBoids_dist);
  }

  double meanBoids_speed{0.};
  double meanBoids_speed2{0.};

  const std::array<double, 2> sum =
      std::accumulate(flock_.begin(), flock_.begin() + nBoids_, std::array<double, 2>{0., 0.},
                      [](std::array<double, 2>& acc, const std::shared_ptr<bird::Bird>& bird) {
                        acc[0] += bird->getVelocity().module();
                        acc[1] += bird->getVelocity().module() * bird->getVelocity().module();
                        return acc;
                      });
  assert(nBoids_ > 0 && "Flock must contain at least one element");
  meanBoids_speed = sum[0] / nBoids_;
  meanBoids_speed2 = sum[1] / nBoids_;

  const double dev_speed = std::sqrt(meanBoids_speed2 - meanBoids_speed * meanBoids_speed);

  return {meanBoids_dist, dev_dist, meanBoids_speed, dev_speed};
}
} // namespace flock