#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <vector>

#include "../include/bird.hpp"
#include "../include/statistics.hpp"

class Flock {
 private:
  // std::vector<std::unique_ptr<Predator>> predators_;

  const int nBoids_ = 200;
  const int nPredators_ = 3;

  std::vector<std::shared_ptr<Bird>> flock_;


  const sf::Color bColor_ = sf::Color::Blue;
  const sf::Color pColor_ = sf::Color::Red;

  const double maxSpeed_ = 10.;
  const double minSpeed_ = 8.;

  const double s_ = 0.6;
  const double a_ = 0.6;
  const double c_ = 0.001;

  const double d_ = 75.;
  const double ds_ = 20.;

  const double turnFactor_ = 1;
  const double margin_ = 200.;

 public:
  Flock();
  void generateBirds();
  std::vector<std::shared_ptr<Bird>> findNearBoids(Bird&);
  std::vector<std::shared_ptr<Bird>> findNearPredators(Bird&);

  std::array<Point, 2> updateBird(std::shared_ptr<Bird>, sf::VertexArray &, int);
  void evolve(std::vector<sf::VertexArray> &);

  int getBoidsNum() const;
  int getPredatorsNum() const;
  int getFlockSize() const;

  // void vertex(std::vector<sf::Vertex> &);

  Statistics statistics();
};
#endif