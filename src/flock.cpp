
#include "../include/flock.hpp"

#include <SFML/Graphics/VertexArray.hpp>
#include <array>
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

using namespace graphic_par;
using namespace triangles;

Flock::Flock() {
  flock_.resize(nBoids_ + nPredators_);
};

std::vector<std::shared_ptr<Bird>> Flock::getFlock() const { return flock_; };
int Flock::getBoidsNum() const { return nBoids_; };
int Flock::getPredatorsNum() const { return nPredators_; };
int Flock::getFlockSize() const { return (nPredators_ + nBoids_); };

std::vector<std::shared_ptr<Bird>> Flock::findNearBoids(const Bird& target) {
  std::vector<std::shared_ptr<Bird>> near;

  for (int i = 0; i < nBoids_; ++i) {
    if (&target != flock_[i].get() && target.get_position().distance(flock_[i]->get_position()) < d_) {
      near.push_back(flock_[i]);
    }
  }
  return near;
};
std::vector<std::shared_ptr<Bird>> Flock::findNearPredators(const Bird& target) {
  std::vector<std::shared_ptr<Bird>> near;

  for (int i = nBoids_; i < nBoids_ + nPredators_; ++i) {
    if (&target != flock_[i].get() && target.get_position().distance(flock_[i]->get_position()) < d_) {
      near.push_back(flock_[i]);
    }
  }
  return near;
};

std::array<Point, 2> Flock::updateBird(const std::shared_ptr<Bird>& b, sf::VertexArray& triangle, const int i) {
  Point p = b->get_position();
  Point v = b->get_velocity();

  std::vector<std::shared_ptr<Bird>> near_boids{this->findNearBoids(*b)};
  std::vector<std::shared_ptr<Bird>> near_predators{this->findNearPredators(*b)};

  if (i < nBoids_) {
    if (!near_boids.empty()) {
      v += b->separation(s_, ds_, near_boids) + std::dynamic_pointer_cast<Boid>(b)->alignment(a_, near_boids) +
           std::dynamic_pointer_cast<Boid>(b)->cohesion(c_, near_boids);
    }

    if (!near_predators.empty()) {
      // implementare funzione repel dai predatori, potrebbe essere separation, da capire
    }
  } else {
    if (!near_boids.empty()) {
      // implementare funzione chase, da capire
    }
    if (!near_predators.empty()) {
      v += std::dynamic_pointer_cast<Predator>(b)->separation(s_, ds_, near_predators);
    }
  }

  v = b->border(margin_, turnFactor_, v);
  b->friction(maxSpeed_, v);
  b->boost(minSpeed_, v);

  const double d_theta{-1*(b->get_velocity().angle() - v.angle())};  // controllare segno
  // rotateTriangle(b, triangle, d_theta, i);
  p += dt * v;
  return {p, v};
};

void Flock::evolve(sf::VertexArray& triangles) {
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
  for (size_t i = 0; i < flock_.size(); ++i) {
    if (!flock_[i]) {
      std::cerr << "flock_[" << i << "] è nullo!" << std::endl;
    }
  }
}

Statistics Flock::statistics() {
  double meanBoids_dist{0.};
  double meanBoids_dist2{0.};

  for (std::vector<std::shared_ptr<Bird>>::iterator it = flock_.begin(); it != flock_.begin() + nBoids_; ++it) {
    std::array<double, 2> sum = std::accumulate(it, flock_.begin() + nBoids_, std::array<double, 2>{0., 0.},
                                                [&it](std::array<double, 2>& acc, std::shared_ptr<Bird>& bird) {
                                                  acc[0] += (bird->get_position().distance((*it)->get_position()));
                                                  acc[1] +=
                                                      std::pow(bird->get_position().distance((*it)->get_position()), 2);
                                                  return acc;
                                                });
    meanBoids_dist += sum[0] / (nBoids_ * (nBoids_ - 1) / 2.);
    meanBoids_dist2 += sum[1] / (nBoids_ * (nBoids_ - 1) / 2.);
  }

  const double dev_dist = std::sqrt((meanBoids_dist2 - std::pow(meanBoids_dist, 2)));

  double meanBoids_speed{0.};
  double meanBoids_speed2{0.};

  const std::array<double, 2> sum =
      std::accumulate(flock_.begin(), flock_.begin() + nBoids_, std::array<double, 2>{0., 0.},
                      [](std::array<double, 2>& acc, const std::shared_ptr<Bird>& bird) {
                        acc[0] += bird->get_velocity().module();
                        acc[1] += std::pow(bird->get_velocity().module(), 2);

                        return acc;
                      });

  meanBoids_speed = sum[0] / nBoids_;
  meanBoids_speed2 = sum[1] / nBoids_;

  double dev_speed = std::sqrt((meanBoids_speed2) - (std::pow(meanBoids_speed, 2)));

  return {meanBoids_dist, dev_dist, meanBoids_speed, dev_speed};
};
