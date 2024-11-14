#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>

#include "../include/boid.hpp"
#include "../include/point.hpp"
#include "../include/statistics.hpp"


class Flock {
 private:
  std::vector<std::unique_ptr<Boid>> flock_;

  const double N_ = 200;
  const sf::Color color_ = sf::Color::Blue;

  const double maxSpeed_ = 10.;
  const double minSpeed_ = 8.;

  const double s_ = 0.6;
  const double a_ = 0.6;
  const double c_ = 0.001;

  const double d_ = 75.;
  const double ds_ = 20.;

  const double turnFactor_ = 1;
  const double margin_ = 200.;

  const float baseWidth_ = 7;
  const float height_ = 15;

 public:
  Flock();

  std::unique_ptr<Boid> update_boid(std::unique_ptr<Boid> &);
  std::vector<Boid *> findNear(std::unique_ptr<Boid> &);

  void generateBoid();
  void evolve();

  int get_size() const;
  void vertex(std::vector<sf::Vertex> &);
  std::vector<sf::VertexArray> createTriangle(std::vector<sf::Vertex> &);

  void print();

  Statistics statistics();
};
#endif