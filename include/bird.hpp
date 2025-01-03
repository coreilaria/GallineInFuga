/// @file       ../include/bird.hpp
/// @brief      Defines the Bird class.
///
/// @details    This file contains the definition of Bird class, Boid class and Predator class which inherit publicly
///             from Bird. A Bird object represent a bird flying in a two dimension space, each bird is characterized by
///             two Point objects, a position and a velocity, and a double representing the sigh angle they could
///             perceive.
#ifndef BIRD_HPP
#define BIRD_HPP

#include <memory>
#include <vector>

#include "../include/point.hpp"
using namespace point;

namespace bird {

class Bird {
  /// @brief The Bird class represents a bird in the simulation.
  /// @param position_ Is the position of the bird.
  /// @param velocity_ Is the velocity of the bird.
  /// @param sightAngle_ Is the angle of sight of the bird.
 protected:
  Point position_;
  Point velocity_;
  double sightAngle_{};

 public:
  Bird() = default;

  /// @brief Parametric constructor of Bird class.
  /// @details Initialize the position and the velocity of the bird with given Point objects.
  /// @param position Position of the bird.
  /// @param velocity Velocity of the bird.
  Bird(Point const &position, Point const &velocity);

  /// @brief Get the position of the bird.
  /// @return The position of the bird.
  [[nodiscard]] virtual Point getPosition() const;

  /// @brief Get the velocity of the bird.
  /// @return The velocity of the bird.
  [[nodiscard]] virtual Point getVelocity() const;

  /// @brief Set the position and the velocity of the bird.
  /// @param position The position of the bird.
  /// @param velocity The velocity of the bird.
  virtual void setBird(Point position, Point velocity);

  /// @brief Update the velocity of the bird in order to keep it within the border.
  /// @details Whenever the bird is inside the margin, its velocity would be corrected in order to bring it away from
  /// the border of the window. In particular, the increment would be in the direction of the opposite border.
  /// @param margin Identifies the region in which the rule is applied .
  /// @param turn_factor Identifies the increment applied to the components of the velocity.
  /// @return The velocity of the bird with the correction needed.
  virtual Point border(double margin, double turn_factor);

  /// @brief Evaluate the correction to the bird's velocity, in order to keep it separated from other birds.
  /// @details Whenever a bird sees other birds near it, a component of velocity is evaluated in order to keep it
  /// away from the near birds. In particular, the increment depends on the average of the differences in positions,
  /// between the bird and its neighbours.
  /// @param s Factor which modules the correction.
  /// @param ds Identifies the region where it is possible to find neighbours.
  /// @param near Identifies the bird's neighbours.
  /// @return The correction to the velocity.
  virtual Point separation(double s, double ds, std::vector<std::shared_ptr<Bird>> &near);

  virtual void friction(const double[2], Point &) = 0;
  virtual void boost(const double[2], Point &) = 0;

  virtual ~Bird();
};

class Boid final : public Bird {
 public:
  Boid();

  /// @brief Constructs a new Boid object, with given position and velocity, and initializes the sight angle for boids.
  /// @param pos Is the position of the boid.
  /// @param vel Is the boid's velocity.
  Boid(Point const &pos, Point const &vel);

  /// @brief Updates the boid's speed by imposing a maximum speed.
  /// @details If the boid's speed exceeds the maximum allowed, its module is normalized, leaving the
  /// direction unchanged.
  /// @param maxSpeed The component [0] identifies the maximum speed for the boids.
  /// @param velocity Is the velocity to update.
  void friction(const double maxSpeed[2], Point &velocity) override;

  /// @brief Updates the boid's speed by imposing a minimum speed.
  /// @details If the boid's speed is inferior to the minimum allowed, its module is normalized, leaving the
  /// direction unchanged.
  /// @param minSpeed The component [0] identifies the minimum speed for the boids.
  /// @param velocity Is the velocity to update.
  void boost(const double minSpeed[2], Point &velocity) override;

  /// @brief Evaluates the correction to the boid's velocity, in order to keep it aligned with the neighbours.
  /// @details Whenever a boid sees other boids near it, a component of velocity is evaluated in order to keep it
  /// aligned to the near birds. In particular, the increment depends on the average of the neighbours' velocities, from which the boid's velocity itself is subtracted.
  /// @param a Factor which modules the correction.
  /// @param near Identifies the boid's neighbours.
  /// @return The correction to the velocity.
  Point alignment(double a, std::vector<std::shared_ptr<Bird>> &near) const;

  /// @brief Evaluates the correction to the boid's velocity, in order to keep a more cohesive unit of boids.
  /// @details Whenever a boid sees other boids near it, would be evaluated a component of velocity in order make them a
  /// cohesive group. In particular, the increment depends on the average of the neighbours' positions, from
  /// which the boid's velocity itself is subtracted.
  /// @param c Factor which modules the correction.
  /// @param near Identifies the boid's neighbours.
  /// @return The correction to the velocity.
  Point cohesion(double c, std::vector<std::shared_ptr<Bird>> &near) const;

  /// @brief Evaluates the correction to the boid's velocity, in order to keep it separated from predators.
  /// @details Whenever a boid sees predators near it, would be evaluated a component of velocity in order to keep it
  /// away from the predator and prevent it from being caught.  In particular, the increment depends on the average of
  /// the differences in positions, between the bird and the near predators.
  /// @param s Factor which modules the correction.
  /// @param near Identifies the predators near the boid.
  /// @return The correction to the velocity.
  Point repel(double s, std::vector<std::shared_ptr<Bird>> &near) const;
};

class Predator final : public Bird {
 public:
  Predator();
  /// @brief Constructs a new Predator object, with given position and velocity and initializes the sight angle for
  /// predators.
  /// @param pos Is the position of the boid.
  /// @param vel Is the boid's velocity.
  Predator(Point const &pos, Point const &vel);

  /// @brief Updates the speed of the predator by imposing a maximum speed.
  /// @details If the speed of the predator exceeds the maximum allowed, its module is normalized, leaving the
  /// direction unchanged.
  /// @param maxSpeed The component [1] identifies the maximum speed for the predators.
  /// @param velocity Is the velocity to update.
  void friction(const double maxSpeed[2], Point &velocity) override;

  /// @brief Updates the speed of the predator by imposing a minimum speed.
  /// @details If the speed of the predator is inferior to the minimum allowed, its module is normalized, leaving the
  /// direction unchanged.
  /// @param minSpeed The component [1] identifies the minimum speed for the predators.
  /// @param velocity Is the velocity to update.
  void boost(const double minSpeed[2], Point &velocity) override;

  /// @brief Evaluates the correction to the velocity of the predator, in order to chase the near boids.
  /// @details Whenever a predator sees boids near it, a component of velocity is evaluated so that the predators
  /// begin to chase them. In particular, the increment depends on the average of the differences in positions,
  /// between the predator and the near boids.
  /// @param s Factor which modules the correction.
  /// @param near Identifies the boids near the predator.
  /// @return The correction to the velocity.
  Point chase(double s, std::vector<std::shared_ptr<Bird>> &near) const;
};
}  // namespace bird
#endif