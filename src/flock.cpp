
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

using namespace graphic_par;
using namespace triangles;

Flock::Flock() { flock_.resize(nBoids_ + nPredators_); };

std::vector<std::shared_ptr<Bird>> Flock::getFlock() const { return flock_; };
int Flock::getBoidsNum() const { return nBoids_; };
int Flock::getPredatorsNum() const { return nPredators_; };
int Flock::getFlockSize() const { return (nPredators_ + nBoids_); };

// ha senso passare uno shared ptr by reference?
std::vector<std::shared_ptr<Bird>> Flock::findNearBoids(const Bird& target, const int i) const {
  std::vector<std::shared_ptr<Bird>> near;

  const double beta {target.get_velocity().angle()};
  double alpha {};

  // trova i boids vicini per i boids e per i predatori
  for (int j = 0; j < nBoids_; ++j) {
    if (i < nBoids_) {
      // boid vede altri boid vicini
      if (&target != flock_[j].get() && target.get_position().distance(flock_[j]->get_position()) < d_) {
      alpha = (target.get_position() - flock_[j]->get_position()).angle();

        if ((alpha - beta) < (2. / 3 * M_PI) || (alpha - beta) > (2 * M_PI - 2. / 3 * M_PI)) {
          near.push_back(flock_[j]);
        }
      }
    } else {
      //predatore che vede i boids vicini
      if (&target != flock_[j].get() && target.get_position().distance(flock_[j]->get_position()) < d_ * 3.5) {
        alpha = (target.get_position() - flock_[j]->get_position()).angle();

        if ((alpha - beta) < (1./2* M_PI) || (alpha - beta) > (2 * M_PI - 1./2 * M_PI)) {
          near.push_back(flock_[j]);
        }
      }
    }
  }
  return near;
};
std::vector<std::shared_ptr<Bird>> Flock::findNearPredators(const Bird& target, const int i) const {
  std::vector<std::shared_ptr<Bird>> near;
  const double beta {target.get_velocity().angle()};
  double alpha {};

  for (int j = nBoids_; j < nBoids_ + nPredators_; ++j) {
    if (&target != flock_[j].get() && target.get_position().distance(flock_[j]->get_position()) < d_) {
      alpha = (target.get_position() - flock_[j]->get_position()).angle();

      if (i < nBoids_) {
        //boid che vede predatore vicino
      if ((alpha - beta) < (2. / 3 * M_PI) || (alpha - beta) > (2 * M_PI - 2. / 3 * M_PI)) {
        near.push_back(flock_[j]);
      }

      } else {
        //predatore che vede predatore vicino
        if ((alpha - beta) < (1./2* M_PI) || (alpha - beta) > (2 * M_PI - 1./2 * M_PI)) {
          near.push_back(flock_[j]);
        }
      }

    }
  }
  return near;
};

std::array<Point, 2> Flock::updateBird(const std::shared_ptr<Bird>& b, sf::VertexArray& triangle, const int i) const {
  Point p = b->get_position();
  Point v = b->get_velocity();

  std::vector<std::shared_ptr<Bird>> near_boids{this->findNearBoids(*b, i)};
  std::vector<std::shared_ptr<Bird>> near_predators{this->findNearPredators(*b, i)};

  if (i < nBoids_) {
    if (!near_predators.empty()) {
      v += std::dynamic_pointer_cast<Boid>(b)->repel(s_, near_predators);
    }
    if (!near_boids.empty()) {
      v += b->separation(s_, ds_, near_boids) + std::dynamic_pointer_cast<Boid>(b)->alignment(a_, near_boids) +
           std::dynamic_pointer_cast<Boid>(b)->cohesion(c_, near_boids);
    }
  } else {
    if (!near_predators.empty()) {
      v += b->separation(s_ * 0.1, d_ * 0.5, near_predators);
    }
    if (!near_boids.empty()) {
      v += std::dynamic_pointer_cast<Predator>(b)->chase(c_, near_boids);
    }
  }

  v = b->border(margin_, turnFactor_, v);
  b->friction(maxSpeed_, v);
  b->boost(minSpeed_, v);

  const double d_theta{b->get_velocity().angle() - v.angle()};  // controllare segno
  p += dt * v;
  rotateTriangle(b, triangle, d_theta, i);
  return {p, v};
};

void Flock::evolve(sf::VertexArray& triangles) const {
  std::vector<Point> pos;
  std::vector<Point> vel;

  for (int i = 0; i < nBoids_ + nPredators_; ++i) {
    // Aggiorna il Boid esistente e crea un nuovo shared_ptr con il risultato
    std::array<Point, 2> p = this->updateBird(flock_[i], triangles, i);
    pos.push_back(p[0]);
    vel.push_back(p[1]);
  }
  for (int i = 0; i < nBoids_ + nPredators_; ++i) {
    flock_[i]->set_position(pos[i]);
    flock_[i]->set_velocity(vel[i]);
  }
};

void Flock::generateBirds() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist_pos_x(statsWidth, windowWidth);
  std::uniform_real_distribution<double> dist_pos_y(0., windowHeight);
  std::uniform_real_distribution<double> dist_vel_x(minVel_x, maxVel_x);
  std::uniform_real_distribution<double> dist_vel_y(minVel_y, maxVel_y);

  std::vector<Boid> boids;
  std::vector<Predator> predators;
  // emplace_back viene utilizzato per costruire direttamente gli oggetti all'interno dei vettori
  // senza creare copie temporanee
  boids.reserve(nBoids_);
  for (int i = 0; i < nBoids_; ++i) {
    boids.emplace_back(Point(dist_pos_x(rng), dist_pos_y(rng)), Point(dist_vel_x(rng), dist_vel_y(rng)));
  }
  predators.reserve(nPredators_);
  for (int i = 0; i < nPredators_; ++i) {
    predators.emplace_back(Point(dist_pos_x(rng), dist_pos_y(rng)), Point(dist_vel_x(rng), dist_vel_y(rng)));
  }

  flock_.clear();

  for (const auto& boid : boids) {
    flock_.push_back(std::make_shared<Boid>(boid));  // Usa std::make_shared per creare shared_ptr
  }
  for (const auto& predator : predators) {
    flock_.push_back(std::make_shared<Predator>(predator));  // Usa std::make_shared per creare shared_ptr
  }
  assert(!flock_.empty());
  for (const auto& bird : flock_) {
    assert((bird != nullptr) && "Nullptr found in flock_ vector");
  }
}

Statistics Flock::statistics() {
  double meanBoids_dist{0.};
  double meanBoids_dist2{0.};

  for (auto it = flock_.begin(); it != flock_.begin() + nBoids_; ++it) {
    std::array<double, 2> sum = std::accumulate(it, flock_.begin() + nBoids_, std::array<double, 2>{0., 0.},
                                                [&it](std::array<double, 2>& acc, const std::shared_ptr<Bird>& bird) {
                                                  acc[0] += (bird->get_position().distance((*it)->get_position()));
                                                  acc[1] +=
                                                      std::pow(bird->get_position().distance((*it)->get_position()), 2);
                                                  return acc;
                                                });
    assert(nBoids_ > 1 && "Flock must contain at least two elements");
    meanBoids_dist += sum[0] / (nBoids_ * (nBoids_ - 1) / 2.);
    meanBoids_dist2 += sum[1] / (nBoids_ * (nBoids_ - 1) / 2.);
  }

  const double dev_dist = std::sqrt(meanBoids_dist2 - meanBoids_dist * meanBoids_dist);

  double meanBoids_speed{0.};
  double meanBoids_speed2{0.};

  const std::array<double, 2> sum =
      std::accumulate(flock_.begin(), flock_.begin() + nBoids_, std::array<double, 2>{0., 0.},
                      [](std::array<double, 2>& acc, const std::shared_ptr<Bird>& bird) {
                        acc[0] += bird->get_velocity().module();
                        acc[1] += std::pow(bird->get_velocity().module(), 2);

                        return acc;
                      });
  assert(nBoids_ > 1 && "Flock must contain at least two elements");
  meanBoids_speed = sum[0] / nBoids_;
  meanBoids_speed2 = sum[1] / nBoids_;

  double dev_speed = std::sqrt((meanBoids_speed2) - (meanBoids_speed * meanBoids_speed));

  return {meanBoids_dist, dev_dist, meanBoids_speed, dev_speed};
};
