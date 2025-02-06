/// @file       ../include/flock.hpp
/// @brief      Defines the Flock class.
///
/// @details    This file contains the definition of Flock class.
///             The Flock represents the group of bird::Bird objects, divided in bird::Boid and bird::Predator, flying
///             in the simulation.

#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "../include/bird.hpp"
#include "../include/statistics.hpp"

namespace flock {

/// @brief The Flock class represents a group of birds, composed of bird::Boid objects and bird::Predator objects.
class Flock {
 private:
  size_t n_boids_;
  size_t n_predators_;

  std::vector<std::shared_ptr<bird::Boid>> b_flock_;
  std::vector<std::shared_ptr<bird::Predator>> p_flock_;

  static constexpr double b_sight_angle_ = 2. / 3 * M_PI;
  static constexpr double p_sight_angle_ = 0.5 * M_PI;

  /// @brief Is the parameter which modules the separation of the bird::Boid and bird::Predator objects in the flock.
  double s_;

  /// @brief Is the parameter which modules the alignment of the bird::Boid objects in the flock.
  double a_;

  /// @brief Is the parameter which modules the cohesion of the bird::Boid objects in the flock.
  double c_;

  /// @brief Is the parameter which modules the repulsion coefficient for bird::Boid objects in the flock.
  double r_;

  /// @brief Is the parameter which modules the chase coefficient for bird::Predator objects in the flock.
  double ch_;

  /// @brief Is the radius of the circle where the nearby bird::Boid objects and bird::Predator objects can be located.
  static constexpr double d_ = 75.;

  /// @brief Is the radius of the circle where the separation rule for bird::Boid objects is effective.
  static constexpr double b_ds_ = 20.;

  /// @brief Is the radius of the circle where the separation rule for bird::Predator objects is effective.
  static constexpr double p_ds_ = d_ * 0.5;

  /// @brief Is the increment that is applied to the velocity when a bird::Boid object or a bird::Predator object flies
  /// too close to the border of the window.
  static constexpr double turn_factor_ = 2.5;

  /// @brief Is the distance from the border of the window within which the border rule applies.
  static constexpr double margin_ = 100.;

  double b_max_speed_;
  double p_max_speed_;

  double b_min_speed_;
  double p_min_speed_;

 public:
  /// @brief Constructs a new Flock object.
  /// @param nBoids Number of bird::Boid objects.
  /// @param nPredators Number of bird::Predator objects.
  /// @details Initializes n_boids_ and n_predators_ with the given parameters and sets:
  /// - s_ = 0.1
  /// - a_ = 0.1
  /// - c_ = 0.004
  /// - r_ = 0.6
  /// - ch_ = 0.008
  /// - b_max_speed_ = 12.
  /// - p_max_speed_ = 8.
  /// - b_min_speed_ = 7.
  /// - p_min_speed_ = 5.
  Flock(size_t nBoids, size_t nPredators);

  /// @brief Constructs a new Flock object.
  /// @param boids Vector of std::shared_ptr<bird::Boid> objects.
  /// @param predators Vector of std::shared_ptr<bird::Predator> objects.
  /// @param bMaxSpeed Maximum value of speed for bird::Boid objects.
  /// @param pMaxSpeed Maximum value of speed for bird::Predator objects.
  /// @param bMinSpeed Minimum value of speed for bird::Boid objects.
  /// @param pMinSpeed Minimum value of speed for bird::Predator objects.
  /// @details Initializes b_flock_, p_flock_, b_max_speed_, p_max_speed_, b_min_speed_, p_min_speed_ with the
  /// given parameters and sets:
  /// - n_boids_ with the size of the parameter boids
  /// - n_predators_ with the size of the parameter predators
  /// - s_ = 0.1
  /// - a_ = 0.1
  /// - c_ = 0.004
  /// - r_ = 0.6
  /// - ch_ = 0.008
  Flock(const std::vector<std::shared_ptr<bird::Boid>>& boids,
        const std::vector<std::shared_ptr<bird::Predator>>& predators, double bMaxSpeed, double pMaxSpeed,
        double bMinSpeed, double pMinSpeed);

  /// @brief Gets the number of bird::Boid objects in the flock.
  /// @return The number of bird::Boid objects.
  [[nodiscard]] size_t getBoidsNum() const;

  /// @brief Gets the number of bird::Predator objects in the flock.
  /// @return The number of bird::Predator objects.
  [[nodiscard]] size_t getPredatorsNum() const;

  /// @brief Gets the number of bird::Boid objects and bird::Predator objects in the flock.
  /// @return The sum of the number of bird::Boid objects and bird::Predator objects in the flock.
  [[nodiscard]] size_t getFlockSize() const;

  /// @brief Gets the vector of shared pointers to the bird::Boid objects in the flock.
  /// @return The vector of std::shared_ptr<bird::Boid> objects.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Boid>> getBoidFlock() const;

  /// @brief Gets the vector of shared pointers to the bird::Predator objects in the flock.
  /// @return The vector of std::shared_ptr<bird::Predator> objects.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Predator>> getPredatorFlock() const;

  /// @brief Gets the turn factor for the border rule.
  /// @return The turn factor.
  [[nodiscard]] static double getTurnFactor();

  /// @brief Gets the margin for the border rule.
  /// @return The margin.
  [[nodiscard]] static double getMargin();

  /// @brief Returns an array containing the flight parameters of the flock.
  /// @details Returns an array containing the separation coefficient s_,
  /// the alignment coefficient a_, the cohesion coefficient c_ and the repulsion coefficient r_ and the chase
  /// coefficient ch_ in the stated order.
  /// @return The array containing the values of the parameters s_, a_, c_, r_, ch_.
  [[nodiscard]] std::array<double, 5> getFlightParams() const;

  /// @brief Returns an array containing the values of the parameters d_, b_ds_, p_ds_.
  /// @details Returns an array containing the parameters d_, b_ds_, p_ds_ in the stated order.
  /// The first one represents the radius of the circle within which the nearby bird::Boid objects and bird::Predator
  /// objects can be found, the second and the third one represent the radius of the circle within which the separation
  /// rule is applied, respectively for bird::Boid and bird::Predator objects.
  /// @return The array containing the values of the parameters d_, b_ds_, p_ds_.
  [[nodiscard]] static std::array<double, 3> getDistancesParams();

  /// @brief Sets the flight parameters s_, a_, c_ and r_ of the flock with the values streamed from input.
  /// @param in Is the input stream.
  /// @param out Is the output stream.
  void setFlightParams(std::istream& in, std::ostream& out);

  /// @brief Generates bird::Boid and bird::Predator objects to fill the flock.
  /// @details bird::Boid and bird::Predator objects are generated with random positions and velocities, then the
  /// b_flock_ vector and the p_flock_ vector are filled with the shared pointers to these objects.
  void generateBirds();

  /// @brief Finds bird::Boid objects near a bird::Boid object or a bird::Predator object.
  /// @param i Is the index identifying the position of the shared pointer to the current object
  /// either in the b_flock_ vector or in the p_flock_ vector.
  /// @param is_boid Is a boolean constant which states whether the current object is a bird::Boid object or a
  /// bird::Predator object.
  /// @return The vector containing the pointers to the bird::Boid objects near the current bird.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> findNearBoids(size_t i, bool is_boid) const;

  //// @brief Finds bird::Boid objects near a bird::Boid object or a bird::Predator object.
  /// @param i Is the index identifying the position of the shared pointer to the current object
  /// either in the b_flock_ vector or in the p_flock_ vector.
  /// @param is_boid Is a boolean constant which states whether the current object is a bird::Boid object or a
  /// bird::Predator object.
  /// @return The vector containing the pointers to the bird::Predator objects near the current bird.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> findNearPredators(size_t i, bool is_boid) const;

  /// @brief Evaluates the new position and velocity of a bird in the flock.
  /// @details Evaluates a new velocity for a bird::Boid object or a bird::Predator object, taking into account the
  /// rules implemented for each class:
  ///  - separation
  ///  - border
  ///  - friction
  ///  - boost
  ///  - alignment (only for bird::Boid objects)
  ///  - cohesion (only for bird::Boid objects)
  ///  - repel (only for bird::Boid objects)
  ///  - chase (only for bird::Predator objects)
  ///  Then evaluates the new position by multiplying the new velocity by graphic_par::dt. Eventually updates the
  ///  position and orientation of the triangle associated with the bird::Boid or bird::Predator object.
  /// @param triangles Is the array containing the triangle associated with the bird.
  /// @param i Is the index identifying the position of a bird::Boid object in the b_flock_ vector or a bird::Predator
  /// object in the p_flock_ vector.
  /// @param is_boid Is a boolean constant which states whether the current object is a bird::Boid object or a
  /// bird::Predator object.
  /// @return The array containing, respectively, the updated position and velocity of the bird.
  std::array<point::Point, 2> updateBird(sf::VertexArray& triangles, size_t i, bool is_boid) const;

  /// @brief Updates the position and the orientation of the triangles associated with the birds in the flock.
  /// @details Updates the velocity and position of each bird::Boid and bird::Predator object in the flock. Then the
  /// position and the orientation of the associated triangles are updated.
  /// @param triangles Array of triangles associated with each bird in the flock.
  void evolve(sf::VertexArray& triangles) const;

  /// @brief Evaluates the relevant statistical quantities for the bird::Boid objects in the flock.
  /// @details It computes:
  /// - mean distance between boids
  /// - standard deviation of the distance between each boid
  /// - mean speed of the boids
  /// - standard deviation of the speed of the boids
  ///@return A statistics::Statistics object.
  [[nodiscard]] statistics::Statistics statistics() const;
};
}  // namespace flock
#endif