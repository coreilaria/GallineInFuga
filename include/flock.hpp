#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <vector>

#include "../include/bird.hpp"
#include "../include/statistics.hpp"

class Flock {
 private:
  const int nBoids_ = 300;
  const int nPredators_ = 1;

  std::vector<std::shared_ptr<Bird>> flock_;

  const double maxSpeed_[2]{12., 8.};
  const double minSpeed_[2]{7., 5.};

  // const double s_ = 0.6;
  double a_ = 0.6;
  double s_ = 0.6;
  double c_ = 0.001;

  double d_ = 75.;
  double ds_ = 20.;

  double turnFactor_ = 20.;
  double margin_ = 50.;

 public:
  Flock();

  int getBoidsNum() const;
  int getPredatorsNum() const;
  int getFlockSize() const;
  std::vector<std::shared_ptr<Bird>> getFlock() const;

  void generateBirds();
  std::vector<std::shared_ptr<Bird>> findNearBoids(const Bird &, int) const;
  std::vector<std::shared_ptr<Bird>> findNearPredators(const Bird &, int) const;

  std::array<Point, 2> updateBird(const std::shared_ptr<Bird> &, sf::VertexArray &, int) const;
  void evolve(sf::VertexArray &) const;


  Statistics statistics();
};
#endif