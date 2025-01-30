/// @file       ../include/flock.hpp
/// @brief      Defines the Flock class.
///
/// @details    This file contains the definition of Flock class.
///             The Flock represents the group of bird::Birds, divided in bird::Boids and bird::Predators, flying in the
///             simulation.

#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
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
  std::vector<std::shared_ptr<bird::Bird>> flock_;

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
  double turn_factor_ = 5.;

  /// @param margin_ Is the distance from the border of the window within which the border rule applies.
  double margin_ = 100.;

  /// @param max_speed_ Is an array containing the maximum speed value, respectively for bird::Boids and
  /// bird::Predators.
  std::array<double, 2> max_speed_;

  /// @param min_speed_ Is an array containing the minimum speed value, respectively for bird::Boids and
  /// bird::Predators.
  std::array<double, 2> min_speed_;

 public:
  /// @brief Constructs a new Flock object,
  /// @param nBoids Number of boids.
  /// @param nPredators Number of predators.
  /// @details Initializes n_boids_ and n_predators_ with the given parameters and sets:
  /// - s_ = 0.6
  /// - a_ = 0.6
  /// - c_ = 0.01
  /// - max_speed_ = {12., 8.}
  /// - min_speed_ = {7., 5.}
  Flock(int nBoids, int nPredators);

  /// @brief Constructs a new Flock object,
  /// @param nBoids Number of boids.
  /// @param nPredators Number of predators.
  /// @param maxSpeed Maximum values of speed for boids and predators.
  /// @param minSpeed Minimum values of speed for boids and predators.
  /// @details Initializes n_boids_ and n_predators_, max_speed_, min_speed_ with the given parameters and sets:
  /// - s_ = 0.6
  /// - a_ = 0.6
  /// - c_ = 0.01
  Flock(int nBoids, int nPredators, const std::array<double, 2> &maxSpeed, const std::array<double, 2> &minSpeed);

  /// @brief Gets the number of bird::Boids in the flock.
  /// @return The number of bird::Boids.
  [[nodiscard]] int getBoidsNum() const;

  /// @brief Gets the number of bird::Predators in the flock.
  /// @return The number of bird::Predators.
  [[nodiscard]] int getPredatorsNum() const;

  /// @brief Gets the number of bird::Bird in the flock.
  /// @return The sum of the number of bird::Boids and bird::Predators in the flock.
  [[nodiscard]] int getFlockSize() const;

  /// @brief Gets the flock vector.
  /// @return The vector of bird::Bird in the flock.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> getFlock() const;

  /// @brief Gets the parameters for the rule border.
  /// @return The array containing respectively the margin and the turn factor.
  [[nodiscard]] std::array<double, 2> getBorderParams() const;

  /// @brief Sets the vector of bird::Birds which will form the flock.
  /// @param flock Is the vector of bird::Birds.
  void setFlock(const std::vector<std::shared_ptr<bird::Bird>> &flock);

  /// @brief Sets the flock's flight parameters with the values streamed in input.
  void setFlockParams();

  /// @brief Generates bird::Birds to fill the flock.
  /// @details bird::Boid and bird::Predator objects are generated with random positions and velocities, then the flock
  /// vector is filled with these objects.
  void generateBirds();

  /// @brief Finds the bird::Boids near a bird::Bird.
  /// @param target Is the bird::Bird of which we want to find the bird::Boids nearby.
  /// @param i Is the index identifying the position of the bird::Bird in the flock.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> findNearBoids(const bird::Bird &target, int i) const;

  /// @brief Finds the predators near a bird::Bird.
  /// @param target Is the bird::Bird of which we want to find the bird::Predators nearby.
  /// @param i Is the index identifying the position of the bird::Bird in the flock.
  [[nodiscard]] std::vector<std::shared_ptr<bird::Bird>> findNearPredators(const bird::Bird &target, int i) const;

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
  /// @param b Is the bird::Bird to update.
  /// @param triangles Is the array containing the triangle associated with the bird::Bird.
  /// @param i Is the index identifying the position of the bird::Bird in the flock.
  /// @return The array containing, respectively, the updated position and velocity of the bird::Bird.
  std::array<point::Point, 2> updateBird(const std::shared_ptr<bird::Bird> &b, sf::VertexArray &triangles, int i) const;

  /// @brief Updates the position and the direction of the triangles.
  /// @details It updates the velocity and position of each bird::Bird in the flock. Then the position and the
  /// direction of the associated triangles are updated.
  /// @param triangles Array of triangles associated with each bird::Bird in the flock.
  void evolve(sf::VertexArray &triangles) const;

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