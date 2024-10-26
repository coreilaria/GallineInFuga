#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>

#include "../include/boid.hpp"
#include "../include/constants.hpp"
#include "../include/point.hpp"

class Flock {
 private:
  std::vector<std::unique_ptr<Boid>> flock_;

  const double N_ = 100;

  const double maxSpeed_ = 100;
  const double s_ = 0.7;
  const double a_ = 0.05;
  const double c_ = 0.015;

  const double turnFactor_ = 0.25;
  const double margin_ = 100.;

  const double d_ = 90.;
  const double ds_ = 20.;

 public:
  Flock();
//   Flock(std::vector<Boid*>);

  std::unique_ptr<Boid> update_boid(std::unique_ptr<Boid> &);
  std::vector<Boid*> findNear(std::unique_ptr<Boid>&);

  void generateBoid();
  void evolve();

  int get_size() const;
  void vertex(std::vector<sf::Vertex>&);

  void print();
};
#endif