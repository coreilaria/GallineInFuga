/// @file       ../include/statistics.hpp
/// @brief      Defines the Statistics struct.
///
/// @details    This file contains the definition of Statistics struct.
///             A Statistics object contains all the relevant information for a statistical analysis of the flock.
#ifndef STATISTICS_HPP
#define STATISTICS_HPP

namespace statistics {
struct Statistics {
  ///@param mean_dist Represents the mean value of the distance between each couple of bird::Boid objects, at a fixed time.
  double mean_dist;

  ///@param dev_dist Represents the standard deviation associated with the mean distance between bird::Boid objects.
  double dev_dist;

  ///@param mean_speed Represents the mean value of the speed of each bird::Boid object.
  double mean_speed;

  ///@param dev_speed Represents the standard deviation associated with the mean speedof each bird::Boid object, at a fixed time.
  double dev_speed;

  ///@brief Constructs a Statistics object.
  ///@details Each attribute is initialized to '0.'.
  Statistics();

  ///@brief Constructs a Statistics object.
  ///@details Each attribute is initialized with the given parameters.
  ///@param m_dist Is the mean distance.
  ///@param d_dist Is the standard deviation associated with the mean distance.
  ///@param m_speed Is the mean speed.
  ///@param d_speed Is the standard deviation associated with the mean speed.
  Statistics(double m_dist, double d_dist, double m_speed, double d_speed);
};
}  // namespace statistics

#endif