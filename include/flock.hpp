/// @file       ../include/flock.hpp
/// @brief      Defines the Flock class.
///
/// @details    This file contains the definition of Flock class.
///             The Flock represents the group of birds, divided in boids and predators, flying in the simulation.

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
  /// @brief The Flock class represents the group of birds.
 private:
  /// @param nBoids_ Is number of boids in the flock.
  int nBoids_;

  /// @param nPredators_ Is number of predators in the flock.
  int nPredators_;

  /// @param flock_ Is the vector containing both boids and predators.
  std::vector<std::shared_ptr<Bird>> flock_;

  /// @param maxSpeed_ Is a native array containing the maximum speed value, respectively for boids and predators.
  double maxSpeed_[2];

  /// @param minSpeed_ Is a native array containing the minimum speed value, respectively for boids and predators.
  double minSpeed_[2];

  /// @param s_ Is the parameters which modules the separation of the birds in the flock.
  double s_ = 0.6;

  /// @param a_ Is the parameters which modules the alignment of the boids in the flock.
  double a_ = 0.6;

  /// @param c_ Is the parameters which modules the cohesion of the boids in the flock.
  double c_ = 0.001;

  /// @param d_ Is the radius of the circle where the nearby boids can be located.
  double d_ = 75.;

  /// @param ds_ Is the radius of the circle where the separation rule would be effective.
  double ds_ = 20.;

  /// @param turnFactor_ Is the increment that would be applied to the velocity's component when a bird flies too close
  /// to teh border of the window.
  double turnFactor_ = 5.;

  /// @param margin_ Is the distance from the window's border within which the border rule applies.
  double margin_ = 100.;

 public:
  /// @brief Construct a new Flock object.
  /// @details Set:
  /// - nBoids_ = 0
  /// - nPredators_ = 0
  /// - maxSpeed_ = {12., 8.}
  /// - minSpeed_{7., 5.}
  Flock();

  /// @brief Construct a new Flock object,
  /// @details Initialize nBoids_ and nPredators_ with the given parameters and set:
  /// - maxSpeed_ = {12., 8.}
  /// - minSpeed_{7., 5.}
  Flock(int, int);

  /// @brief Get the number of boids in the flock.
  /// @return The number of boids.
  [[nodiscard]] int getBoidsNum() const;

  /// @brief Get the number of predators in the flock.
  /// @return The number of predators.
  [[nodiscard]] int getPredatorsNum() const;

  /// @brief Get the number of bird in the flock.
  /// @return The sum of the number of boids and predators in the flock.
  [[nodiscard]] int getFlockSize() const;

  /// @brief Get the flock vector.
  /// @return The vector of bird in the flock.
  [[nodiscard]] std::vector<std::shared_ptr<Bird>> getFlock() const;

  /// @brief Get the parameters for the rule border.
  /// @return The array containing respectively the margin and the turn factor.
  [[nodiscard]] std::array<double, 2> getBorderParams() const;

  /// @brief Set the vector of bird which will form the flock.
  /// @param flock Is the vector of bird.
  void setFlock(const std::vector<std::shared_ptr<Bird>> &flock);

  /// @brief Set maximum speed value for both boids and predators.
  /// @param maxSpeed_b The maximum speed for boids.
  /// @param maxSpeed_p The maximum speed for predators.
  void setMaxSpeed(double maxSpeed_b, double maxSpeed_p);

  /// @brief Set minimum speed value for both boids and predators.
  /// @param minSpeed_b The minimum speed for boids.
  /// @param minSpeed_p The minimum speed for predators.
  void setMinSpeed(double minSpeed_b, double minSpeed_p);

  /// @brief Generate birds to fill the flock.
  /// @details Boid and Predator objects are generated with random positions and velocities, then the flock vector is
  /// filled with these objects.
  void generateBirds();

  /// @brief Find the boids near a bird.
  /// @param target Is the bird of which we want to find the boids nearby.
  /// @param i Is the index identifying the position of the bird in the flock.
  std::vector<std::shared_ptr<Bird>> findNearBoids(const Bird &target, int i) const;

  /// @brief Find the predators near a bird.
  /// @param target Is the bird of which we want to find the predators nearby.
  /// @param i Is the index identifying the position of the bird in the flock.
  std::vector<std::shared_ptr<Bird>> findNearPredators(const Bird &target, int i) const;

  /// @brief Evaluate the new position and velocity of a bird in the flock.
  /// @details Evaluate a new velocity for the bird, taking on account all the rules implemented for the birds:
  ///  - separation
  ///  - border
  ///  - friction
  ///  - boost
  ///  - alignment (boids)
  ///  - cohesion (boids)
  ///  - repel (boids)
  ///  - chase (predators)
  ///  Then evaluate the new position by multiplying the new velocity by graphic_par::dt. Eventually update the position
  ///  and rotation of the triangle associated with the bird.
  /// @param b Is the bird to update
  /// @param triangle Is the array containing the triangle associated with the bird.
  /// @param i Is the index identifying the position of the bird in the flock.
  /// @return The array containing, respectively, the updated position and velocity of the bird.
  std::array<Point, 2> updateBird(const std::shared_ptr<Bird> &b, sf::VertexArray &triangle, int i) const;

  /// @brief Update the triangles' position and direction.
  /// @details It updates the velocity and position of each bird in the flock. Then is updated the position and the
  /// direction of the triangles associated.
  /// @param triangles Array of triangles associated with each bird in the flock.
  void evolve(sf::VertexArray &triangles) const;

  /// @brief Evaluate the relevant statistical quantities of the flock.
  /// @details It computes:
  /// - mean distance
  /// - mean distance's standard deviation
  /// - mean speed
  /// - mean speed's standard deviation
  ///@return A Statistics object.
  statistics::Statistics statistics();
};
}  // namespace flock
#endif