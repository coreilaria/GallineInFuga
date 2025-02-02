/// @file       ../include/flock.hpp
/// @brief      Defines the Flock class.
///
/// @details    This file contains the definition of Flock class.
///             The Flock represents the group of bird::Birds, divided in bird::Boids and bird::Predators, flying in the
///             simulation.

#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "../include/bird.hpp"
#include "../include/statistics.hpp"

namespace flock {

class Flock {
  /// @brief The Flock class represents the group of bird::Birds.
 private:
  /// @param n_boids_ Is number of bird::Boids in the flock.
  int n_boids_;

  /// @param n_predators_ Is number of bird::Predators in the flock.
  int n_predators_;

  /// @param flock_ Is the vector containing both bird::Boids and bird::Predators.
  std::vector<std::shared_ptr<bird::Boid>> b_flock_;
  std::vector<std::shared_ptr<bird::Predator>> p_flock_;

  /// @param b_sight_angle_ Is the bird::Boid objects' angle of sight.
  static constexpr double b_sight_angle_ = 2. / 3 * M_PI;

  /// @param p_sight_angle_ Is the bird::Predator objects' angle of sight.
  static constexpr double p_sight_angle_ = 0.5 * M_PI;

  /// @param s_ Is the parameters which modules the separation of the bird::Birds in the flock.
  double s_;

  /// @param a_ Is the parameters which modules the alignment of the bird::Boids in the flock.
  double a_;

  /// @param c_ Is the parameters which modules the cohesion of the bird::Boids in the flock.
  double c_;

  /// @param d_ Is the radius of the circle where the nearby bird::Boids can be located.
  double d_ = 75.;

  /// @param ds_ Is the radius of the circle where the separation rule would be effective.
  double ds_ = 20.;

  /// @param turn_factor_ Is the increment that is applied to the component of the velocity when a bird::Bird flies too
  /// close to the border of the window.
  double turn_factor_ = 2.5;

  /// @param margin_ Is the distance from the border of the window within which the border rule applies.
  double margin_ = 100.;

  /// @param b_max_speed_ Is the maximum speed value for bird::Boid
  double b_max_speed_;

  /// @param p_max_speed_ Is the maximum speed value for bird::Predators.
  double p_max_speed_;

  /// @param b_min_speed_ Is the minimum speed value for bird::Boid
  double b_min_speed_;

  /// @param p_min_speed_ Is the minimum speed value for bird::Predators.
  double p_min_speed_;

 public:
  /// @brief Constructs a new Flock object.
  /// @param nBoids Number of boids.
  /// @param nPredators Number of predators.
  /// @details Initializes n_boids_ and n_predators_ with the given parameters and sets:
  /// - s_ = 0.1
  /// - a_ = 0.1
  /// - c_ = 0.004
  /// - b_max_speed_ = 12.
  /// - p_max_speed_ = 8.
  /// - b_min_speed_ = 7.
  /// - p_min_speed_ = 5.
  Flock(int nBoids, int nPredators);

  /// @brief Constructs a new Flock object.
  /// @param boids Vector of std::shared_ptr<bird::Boid>.
  /// @param predators Vector of std::shared_ptr<bird::Predator>.
  /// @param bMaxSpeed Maximum value of speed for boids.
  /// @param pMaxSpeed Maximum value of speed for predators.
  /// @param bMinSpeed Minimum value of speed for boids.
  /// @param pMinSpeed Minimum value of speed for predators.
  /// @details Initializes b_flock_, p_flock_, b_max_speed_, p_max_speed_, b_min_speed_, p_min_speed_ with the
  /// given parameters and sets:
  /// - n_boids_ with the size of the parameter boids
  /// - n_predators_ with the size of the parameter predators
  /// - s_ = 0.1
  /// - a_ = 0.1
  /// - c_ = 0.004
  Flock(const std::vector<std::shared_ptr<bird::Boid>>& boids,
        const std::vector<std::shared_ptr<bird::Predator>>& predators, double bMaxSpeed, double pMaxSpeed,
        double bMinSpeed, double pMinSpeed);

  /// @brief Gets the number of bird::Boid in the flock.
  /// @return The number of bird::Boid.
  [[nodiscard]] int getBoidsNum() const;

  /// @brief Gets the number of bird::Predators in the flock.
  /// @return The number of bird::Predators.
  [[nodiscard]] int getPredatorsNum() const;

  /// @brief Gets the number of bird::Bird in the flock.
  /// @return The sum of the number of bird::Boids and bird::Predators in the flock.
  [[nodiscard]] int getFlockSize() const;

  /// @brief Gets the vector of boids in the flock.
  /// @return The vector of bird::Boid objects.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Boid>> getBoidFlock() const;

  /// @brief Gets the vector of predators in the flock.
  /// @return The vector of bird::Predator objects.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Predator>> getPredatorFlock() const;

  /// @brief Gets the turn factor for the rule border.
  /// @return The turn factor.
  [[nodiscard]] double getTurnFactor() const;

  /// @brief Gets the margin for the rule border.
  /// @return The margin.
  [[nodiscard]] double getMargin() const;

  /// @brief Sets the flock's flight parameters with the values streamed in input.
  void setFlockParams();

  /// @brief Generates bird::Birds to fill the flock.
  /// @details bird::Boid and bird::Predator objects are generated with random positions and velocities, then the flock
  /// vector is filled with these objects.
  void generateBirds();

  /// @brief Finds bird::Boid objects near a bird.
  /// @param i Is the index identifying the position of the current bird in the flock.
  /// @param is_boid Is a boolean constant which states whether the current bird is a bird::Boid or a bird::Predator.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> findNearBoids(int i, bool is_boid) const;

  /// @brief Finds bird::Predator objects near a bird.
  /// @param i Is the index identifying the position of the current bird in the flock.
  /// @param is_boid Is a boolean constant which states whether the current bird is a bird::Boid or a bird::Predator.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> findNearPredators(int i, bool is_boid) const;

  /// @brief Evaluates the new position and velocity of a bird::Bird in the flock.
  /// @details Evaluates a new velocity for the bird::Bird, taking into account all the rules implemented for the
  /// bird::Birds:
  ///  - separation
  ///  - border
  ///  - friction
  ///  - boost
  ///  - alignment (bird::Boid)
  ///  - cohesion (bird::Boid)
  ///  - repel (bird::Boid)
  ///  - chase (bird::Predator)
  ///  Then evaluates the new position by multiplying the new velocity by graphic_par::dt. Eventually updates the
  ///  position and rotation of the triangle associated with the bird::Bird.
  /// @param triangles Is the array containing the triangle associated with the bird::Bird.
  /// @param i Is the index identifying the position of the bird::Bird in the flock.
  /// @param is_boid Is a boolean constant which states whether the current bird is a bird::Boid or a bird::Predator.
  /// @return The array containing, respectively, the updated position and velocity of the bird::Bird.
  std::array<point::Point, 2> updateBird(sf::VertexArray& triangles, int i, bool is_boid) const;

  /// @brief Updates the position and the direction of the triangles.
  /// @details It updates the velocity and position of each bird::Bird in the flock. Then the position and the
  /// direction of the associated triangles are updated.
  /// @param triangles Array of triangles associated with each bird::Bird in the flock.
  void evolve(sf::VertexArray& triangles) const;

  /// @brief Evaluates the relevant statistical quantities of the flock.
  /// @details It computes:
  /// - mean distance
  /// - standard deviation of the distance
  /// - mean speed
  /// - standard deviation of the speed
  ///@return A Statistics object.
  [[nodiscard]] statistics::Statistics statistics() const;
};
}  // namespace flock
#endif