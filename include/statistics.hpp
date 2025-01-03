/// @file       ../include/statistics.hpp
/// @brief      Defines the Statistics struct.
///
/// @details    This file contains the definition of Statistics struct.
///             A Statistics object contains all the relevant information for a statistical analysis of the flock.
#ifndef STATISTICS_HPP
#define STATISTICS_HPP
namespace statistics {
struct Statistics {
  ///@param meanDist Represent the mean value of the distance between each couple of boids, at a fixed time.
  double meanDist;

  ///@param devDist Represent the standard deviation associated with the mean distance.
  double devDist;

  ///@param meanDist Represent the mean value of the speed of each boid.
  double meanSpeed;

  ///@param devSpeed Represent the standard deviation associated with the mean speed, at a fixed time.
  double devSpeed;

  ///@brief Construct an object Statistics
  ///@details Each attribute is set to 0.
  Statistics();

  ///@brief Construct an object Statistics
  ///@details Each attribute is initialized with the given parameters.
  ///@param m_dist Is the mean distance.
  ///@param d_dist Is the standard deviation associated with the mean distance.
  ///@param m_speed Is the mean speed.
  ///@param d_speed Is the standard deviation associated with the mean speed.
  Statistics(double m_dist, double d_dist, double m_speed, double d_speed);
};
}  // namespace statistics

#endif