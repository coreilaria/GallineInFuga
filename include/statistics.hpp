#ifndef STATISTICS_HPP
#define STATISTICS_HPP
#include "TH1D.h"
#include "flock.hpp"

struct Statistics {
  double mean_dist;
  double dev_dist;
  double mean_speed;
  double dev_speed;

  Statistics();
  Statistics(double, double, double, double);

  Statistics flockStatistics(Flock&);
  std::array<TH1D, 2> histogram(Flock&);
  std::array<sf::Sprite, 2> drawHisto(float);
};

#endif