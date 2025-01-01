#ifndef FLOCK_HPP
#define FLOCK_HPP

// #define TEST_PRIVATE       \
// struct test_inspector_t; \
// friend test_inspector_t;

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <vector>

#include "../include/bird.hpp"
#include "../include/statistics.hpp"

class Flock {
 private:
  int nBoids_;
  int nPredators_;

  std::vector<std::shared_ptr<Bird>> flock_;

  const double maxSpeed_[2]{12., 8.};
  const double minSpeed_[2]{7., 5.};

  double a_ = 0.6;
  double s_ = 0.6;
  double c_ = 0.001;

  double d_ = 75.;
  double ds_ = 20.;

  double turnFactor_ = 20.;
  double margin_ = 50.;

  // TEST_PRIVATE
 public:
  Flock();
  Flock(int, int);

  int getBoidsNum() const;
  int getPredatorsNum() const;
  int getFlockSize() const;
  std::vector<std::shared_ptr<Bird>> getFlock() const;

  void setFlock(const std::vector<std::shared_ptr<Bird>>&);

  void generateBirds();
  std::vector<std::shared_ptr<Bird>> findNearBoids(const Bird &, int) const;
  std::vector<std::shared_ptr<Bird>> findNearPredators(const Bird &, int) const;

  std::array<Point, 2> updateBird(const std::shared_ptr<Bird> &, sf::VertexArray &, int) const;
  void evolve(sf::VertexArray &) const;

  Statistics statistics();
};
#endif