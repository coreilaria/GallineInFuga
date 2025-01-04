/// @file       ../include/bird.hpp
/// @brief      Defines the Bird class.
///
/// @details    This file contains the definition of Bird class, Boid class and Predator class which inherit publicly
///             from Bird. A Bird object represent a bird flying in a two dimension space, each bird is characterized by
///             two point::Point objects, a position and a velocity, and a double representing the sight angle they could
///             perceive.
#ifndef BIRD_HPP
#define BIRD_HPP

#include <memory>
#include <vector>

#include "../include/point.hpp"

namespace bird {

class Bird {
  /// @brief The Bird class represents a bird in the simulation.
  /// @param position_ Is the position of the bird.
  /// @param velocity_ Is the velocity of the bird.
  /// @param sightAngle_ Is the angle of sight of the bird.
 protected:
  point::Point position_;
  point::Point velocity_;
  double sightAngle_{};

 public:
  Bird() = default;

  /// @brief Parametric constructor of Bird class.
  /// @details Initialize the position and the velocity of the bird with given point::Point objects.
  /// @param position Position of the bird.
  /// @param velocity Velocity of the bird.
  Bird(point::Point const &position, point::Point const &velocity);

  /// @brief Get the position of the bird.
  /// @return The position of the bird.
  [[nodiscard]] point::Point getPosition() const;

  /// @brief Get the velocity of the bird.
  /// @return The velocity of the bird.
  [[nodiscard]] point::Point getVelocity() const;

  /// @brief Set the position and the velocity of the bird.
  /// @param position The position of the bird.
  /// @param velocity The velocity of the bird.
  void setBird(point::Point position, point::Point velocity);  // needs to be selected

  /// @brief Update the velocity of the bird in order to keep it into the border.
  /// @details Whenever the bird is inside the margin, his velocity would be corrected in order to bring it away from
  /// the border of the window. In particular, the increment would be in the direction of the opposite border.
  /// @param margin Identifies the region in which the rule is applied .
  /// @param turn_factor Identifies the increment applied to the components of the velocity.
  /// @return The velocity of the bird with the correction needed.
  [[nodiscard]] point::Point border(double margin, double turn_factor) const;

  /// @brief Evaluate the correction to the velocity of the bird, in order to keep it separated from other birds.
  /// @details Whenever a bird sees other birds near it, would be evaluated a component of velocity in order to keep it
  /// away from the near birds. In particular, the increment depends on the average of the differences in positions,
  /// between the bird and its neighbours.
  /// @param s Factor which modules the correction.
  /// @param ds Identifies the region where it is possible to find neighbours.
  /// @param near Identifies the bird's neighbours.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point separation(double s, double ds, const std::vector<std::shared_ptr<Bird>> &near) const;

  /// @brief Pure virtual function to apply friction to a bird's velocity.
  virtual void friction(const std::array<double, 2> &, point::Point &) = 0;

  /// @brief Pure virtual function to apply a boost to a bird's velocity.
  virtual void boost(const std::array<double, 2> &, point::Point &) = 0;

  ///@brief Virtual destructor
  virtual ~Bird() = default;
};

class Boid final : public Bird {
 public:
  Boid();

  /// @brief Construct a new Boid object, with given position and velocity, and initialize the sight angle for boids.
  /// @param pos Is the position of the boid.
  /// @param vel Is the velocity of the boid.
  Boid(point::Point const &pos, point::Point const &vel);

  /// @brief Updates the speed of the boid by imposing a maximum speed.
  /// @details If the speed of the boid exceeds the maximum allowed, its module would be normalized, leaving the
  /// direction unchanged.
  /// @param max_speed The component [0] identifies the maximum speed for the boids.
  /// @param velocity Is the velocity to update.
  void friction(const std::array<double, 2> &max_speed, point::Point &velocity) override;

  /// @brief Updates the speed of the boid by imposing a minimum speed.
  /// @details If the speed of the boid exceeds the minimum allowed, its module would be normalized, leaving the
  /// direction unchanged.
  /// @param min_speed The component [1] identifies the minimum speed for the boids.
  /// @param velocity Is the velocity to update.
  void boost(const std::array<double, 2> &min_speed, point::Point &velocity) override;

  /// @brief Evaluate the correction to the velocity of the boid, in order to keep it aligned with the neighbours.
  /// @details Whenever a boid sees other boids near it, would be evaluated a component of velocity in order to keep it
  /// aligned to the near birds. In particular, the increment depends on the average of the velocities of the
  /// neighbours, from which the velocity of the boid itself is subtracted.
  /// @param a Factor which modules the correction.
  /// @param near Identifies the boid's neighbours.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point alignment(double a, const std::vector<std::shared_ptr<Bird>> &near) const;

  /// @brief Evaluate the correction to the velocity of the boid, in order to keep a more cohesive unit of boids.
  /// @details Whenever a boid sees other boids near it, would be evaluated a component of velocity in order make them a
  /// cohesive group. In particular, the increment depends on the average of the positions of the neighbours, from
  /// which the velocity of the boid itself is subtracted.
  /// @param c Factor which modules the correction.
  /// @param near Identifies the boid's neighbours.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point cohesion(double c, const std::vector<std::shared_ptr<Bird>> &near) const;

  /// @brief Evaluate the correction to the velocity of the boid, in order to keep it separated from predators.
  /// @details Whenever a boid sees predators near it, would be evaluated a component of velocity in order to keep it
  /// away from the predator and prevent it from being caught.  In particular, the increment depends on the average of
  /// the differences in positions, between the bird and the near predators.
  /// @param s Factor which modules the correction.
  /// @param near Identifies the predators near the boid.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point repel(double s, const std::vector<std::shared_ptr<Bird>> &near) const;
};

class Predator final : public Bird {
 public:
  Predator();
  /// @brief Construct a new Predator object, with given position and velocity and initialize the sight angle for
  /// predators.
  /// @param pos Is the position of the boid.
  /// @param vel Is the velocity of the boid.
  Predator(point::Point const &pos, point::Point const &vel);

  /// @brief Updates the speed of the predator by imposing a maximum speed.
  /// @details If the speed of the predator exceeds the maximum allowed, its module would be normalized, leaving the
  /// direction unchanged.
  /// @param max_speed The component [1] identifies the maximum speed for the predators.
  /// @param velocity Is the velocity to update.
  void friction(const std::array<double, 2> &max_speed, point::Point &velocity) override;

  /// @brief Updates the speed of the predator by imposing a minimum speed.
  /// @details If the speed of the predator exceeds the minimum allowed, its module would be normalized, leaving the
  /// direction unchanged.
  /// @param min_speed The component [1] identifies the minimum speed for the predators.
  /// @param velocity Is the velocity to update.
  void boost(const std::array<double, 2> &min_speed, point::Point &velocity) override;

  /// @brief Evaluate the correction to the velocity of the predator, in order to chase the near boids.
  /// @details Whenever a predator sees boids near it, would be evaluated a component of velocity so that the predators
  /// begin to chase them. In particular, the increment depends on the average of the differences in positions,
  /// between the predator and the near boids.
  /// @param s Factor which modules the correction.
  /// @param near Identifies the boids near the predator.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point chase(double s, const std::vector<std::shared_ptr<Bird>> &near) const;
};
}  // namespace bird
#endif