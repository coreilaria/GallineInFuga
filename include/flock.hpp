/// @file       ../include/flock.hpp
/// @brief      Defines the Flock class.
///
/// @details    This file contains the definition of Flock class.
///             The Flock represents the group of bird::Birds, divided in bird::Boids and bird::Predators, flying in the simulation.

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
  /// @param nBoids_ Is number of bird::Boids in the flock.
  int nBoids_;

  /// @param nPredators_ Is number of bird::Predators in the flock.
  int nPredators_;

  /// @param flock_ Is the vector containing both bird::Boids and bird::Predators.
  std::vector<std::shared_ptr<bird::Bird>> flock_;

  /// @param max_speed_ Is an array containing the maximum speed value, respectively for bird::Boids and bird::Predators.
  std::array<double,2 > max_speed_;

  /// @param min_speed_ Is an array containing the minimum speed value, respectively for bird::Boids and bird::Predators.
  std::array<double,2 > min_speed_;

  /// @param s_ Is the parameters which modules the separation of the bird::Birds in the flock.
  double s_ = 0.6;

  /// @param a_ Is the parameters which modules the alignment of the bird::Boids in the flock.
  double a_ = 0.6;

  /// @param c_ Is the parameters which modules the cohesion of the bird::Boids in the flock.
  double c_ = 0.001;

  /// @param d_ Is the radius of the circle where the nearby bird::Boids can be located.
  double d_ = 75.;

  /// @param ds_ Is the radius of the circle where the separation rule would be effective.
  double ds_ = 20.;


  /// @param turnFactor_ Is the increment that is applied to the component of the velocity when a bird::Bird flies too close
  /// to the border of the window.
  double turnFactor_ = 5.;

  /// @param margin_ Is the distance from the border of the window within which the border rule applies.
  double margin_ = 100.;

 public:
  /// @brief Constructs a new Flock object.
  /// @details Sets:
  /// - nBoids_ = 0
  /// - nPredators_ = 0
  /// - maxSpeed_ = {12., 8.}
  /// - minSpeed_{7., 5.}
  Flock();

  /// @brief Constructs a new Flock object,
  /// @details Initializes nBoids_ and nPredators_ with the given parameters and sets:
  /// - maxSpeed_ = {12., 8.}
  /// - minSpeed_ = {7., 5.}
  Flock(int, int);

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
  void setFlock(const std::vector<std::shared_ptr<Bird>> &flock);

  /// @brief Sets maximum speed value for both bird::Boids and bird::Predators.
  /// @param maxSpeed_b The maximum speed for bird::Boids.
  /// @param maxSpeed_p The maximum speed for bird::Predators.
  void setMaxSpeed(double maxSpeed_b, double maxSpeed_p);

  /// @brief Sets minimum speed value for both bird::Boids and bird::Predators.
  /// @param minSpeed_b The minimum speed for bird::Boids.
  /// @param minSpeed_p The minimum speed for bird::Predators.
  void setMinSpeed(double minSpeed_b, double minSpeed_p);

  /// @brief Generates bird::Birds to fill the flock.
  /// @details bird::Boid and bird::Predator objects are generated with random positions and velocities, then the flock vector is
  /// filled with these objects.
  void generateBirds();

  /// @brief Finds the boids near a bird::Bird.
  /// @param target Is the bird::Bird of which we want to find the bird::Boids nearby.
  /// @param i Is the index identifying the position of the bird::Bird in the flock.
  std::vector<std::shared_ptr<Bird>> findNearBoids(const Bird &target, int i) const;

  /// @brief Finds the predators near a bird::Bird.
  /// @param target Is the bird::Bird of which we want to find the bird::Predators nearby.
  /// @param i Is the index identifying the position of the bird in the flock.
  std::vector<std::shared_ptr<Bird>> findNearPredators(const Bird &target, int i) const;

  /// @brief Evaluates the new position and velocity of a bird::Bird in the flock.
  /// @details Evaluates a new velocity for the bird::Bird, taking into account all the rules implemented for the bird::Birds:

  ///  - separation
  ///  - border
  ///  - friction
  ///  - boost
  ///  - alignment (bird::Boid)
  ///  - cohesion (bird::Boid)
  ///  - repel (bird::Boid)
  ///  - chase (bird::Predator)
  ///  Then evaluates the new position by multiplying the new velocity by graphic_par::dt. Eventually updates the position
  ///  and rotation of the triangle associated with the bird::Bird.
  /// @param b Is the bird::Bird to update
  /// @param triangle Is the array containing the triangle associated with the bird::Bird.
  /// @param i Is the index identifying the position of the bird::Bird in the flock.
  /// @return The array containing, respectively, the updated position and velocity of the bird::Bird.
  std::array<Point, 2> updateBird(const std::shared_ptr<Bird> &b, sf::VertexArray &triangle, int i) const;

  
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
  [[nodiscard]]statistics::Statistics statistics() const;
};
}  // namespace flock
#endif