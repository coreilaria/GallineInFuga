#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <vector>

#include "../include/bird.hpp"
#include "../include/statistics.hpp"
using namespace bird;

namespace flock {

class Flock {
 private:
  int nBoids_;
  int nPredators_;

  std::vector<std::shared_ptr<Bird>> flock_;

  double maxSpeed_[2];
  double minSpeed_[2];

  double a_ = 0.6;
  double s_ = 0.6;
  double c_ = 0.001;

  double d_ = 75.;
  double ds_ = 20.;

  double turnFactor_ = 5.;
  double margin_ = 100.;

 public:
  Flock();
  Flock(int, int);

  int getBoidsNum() const;
  int getPredatorsNum() const;
  int getFlockSize() const;
  std::vector<std::shared_ptr<Bird>> getFlock() const;
  std::array<double, 2> getBorderParams() const;

  void setFlock(const std::vector<std::shared_ptr<Bird>> &);
  void setMaxSpeed(double, double);
  void setMinSpeed(double, double);

  void generateBirds();
  std::vector<std::shared_ptr<Bird>> findNearBoids(const Bird &, int) const;
  std::vector<std::shared_ptr<Bird>> findNearPredators(const Bird &, int) const;

  std::array<Point, 2> updateBird(const std::shared_ptr<Bird> &, sf::VertexArray &, int) const;
  void evolve(sf::VertexArray &) const;

  statistics::Statistics statistics();
};
}  // namespace flock
#endif