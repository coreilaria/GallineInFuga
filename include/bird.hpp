/// @file       ../include/bird.hpp
/// @brief      Defines the Bird class.
///
/// @details    This file contains the definition of the Bird class, the Boid class and the Predator class; the last two
/// publicly inherit from Bird. A Bird object represents a bird flying in a two-dimensional space. Each bird is
/// characterized by two point::Point objects, representing its position and its velocity.
#ifndef BIRD_HPP
#define BIRD_HPP

#include <memory>
#include <vector>

#include "../include/point.hpp"

namespace bird {

/// @brief The Bird class represents a bird in the simulation.
class Bird {
 protected:
  /// @param position_ Is the position of the bird.
  point::Point position_;

  /// @param velocity_ Is the velocity of the bird.
  point::Point velocity_;

 public:
  /// @brief Default constructor of Bird class.
  Bird() = default;

  /// @brief Parametric constructor of Bird class.
  /// @details Initializes the position and the velocity of the bird with given point::Point objects.
  /// @param position Is the position of the bird.
  /// @param velocity Is the velocity of the bird.
  Bird(point::Point const &position, point::Point const &velocity);

  /// @brief Gets the position of the bird.
  /// @return The position of the bird.
  [[nodiscard]] point::Point getPosition() const;

  /// @brief Gets the velocity of the bird.
  /// @return The velocity of the bird.
  [[nodiscard]] point::Point getVelocity() const;

  /// @brief Sets the position and the velocity of the bird.
  /// @param position Is the position of the bird.
  /// @param velocity Is the velocity of the bird.
  void setBird(point::Point position, point::Point velocity);

  /// @brief Updates the velocity of the bird in order to keep it into the border.
  /// @details Whenever the bird is inside the margin, his velocity is corrected in order to bring it away from
  /// the border of the window. In particular, the increment is in the direction of the opposite border.
  /// @param margin Identifies the region the rule is applied in.
  /// @param turn_factor Identifies the increment applied to the components of the velocity.
  /// @return The velocity of the bird with the needed correction.
  [[nodiscard]] point::Point border(double margin, double turn_factor) const;

  /// @brief Evaluates the correction to the velocity of the bird, in order to keep it separated from other birds.
  /// @details Whenever a bird sees other birds near it, an additional component of velocity is evaluated in order to
  /// keep it away from the neighbours. In particular, the increment depends on the average of the differences in
  /// positions between the bird and its neighbours.
  /// @param s Factor which modules the correction.
  /// @param ds Identifies the region where it is possible to find neighbours.
  /// @param near_boids Identifies the bird's neighbours.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point separation(double s, double ds,
                                        const std::vector<std::shared_ptr<Bird>> &near_boids) const;

  /// @brief Pure virtual function to apply friction to a bird's velocity.
  virtual void friction(double, point::Point &) = 0;

  /// @brief Pure virtual function to apply a boost to a bird's velocity.
  virtual void boost(double, point::Point &) = 0;

  ///@brief Virtual destructor.
  virtual ~Bird() = default;
};

class Boid final : public Bird {
 public:
  ///@brief Default constructor.
  Boid();

  /// @brief Constructs a new Boid object, with given position and velocity.
  /// @param pos Is the position of the boid.
  /// @param vel Is the velocity of the boid.
  Boid(point::Point const &pos, point::Point const &vel);

  /// @brief Updates the speed of the Boid object by imposing a maximum speed.
  /// @details If the speed of the boid exceeds the maximum allowed, its module is normalized, leaving the
  /// direction unchanged.
  /// @param b_max_speed Is the maximum speed for the boids.
  /// @param velocity Is the velocity to update.
  void friction(double b_max_speed, point::Point &velocity) override;

  /// @brief Updates the speed of the Boid object by imposing a minimum speed.
  /// @details If the speed of the Boid object exceeds the minimum allowed, its module would be normalized, leaving the
  /// direction unchanged.
  /// @param b_min_speed Is the minimum speed for Boid objects.
  /// @param velocity Is the velocity to update.
  void boost(double b_min_speed, point::Point &velocity) override;

  /// @brief Evaluate the correction to the velocity of the Boid object, in order to keep it aligned with the
  /// neighbours.
  /// @details Whenever a boid sees other boids near it, an additional component of velocity is evaluated
  /// in order to keep it aligned to the neighbours. In particular, the increment depends on the average of the
  /// velocities of the near boids, from which the velocity of the boid itself is subtracted.
  /// @param a Factor which modules the correction.
  /// @param near_boids Identifies the boid's neighbours.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point alignment(double a, const std::vector<std::shared_ptr<Bird>> &near_boids) const;

  /// @brief Evaluate the correction to the velocity of the Boid object, in order to keep a more cohesive unit of Boid
  /// objects.
  /// @details Whenever a boid sees other boids near it, an additional component of velocity is evaluated
  /// in order to make them a cohesive group. In particular, the increment depends on the average of the positions of
  /// the neighbours, from which the velocity of the boid itself is subtracted.
  /// @param c Factor which modules the correction.
  /// @param near_boids Identifies the boids neighbours.
  /// @return  The correction to the velocity.
  [[nodiscard]] point::Point cohesion(double c, const std::vector<std::shared_ptr<Bird>> &near_boids) const;

  /// @brief Evaluate the correction to the velocity of the Boid object, in order to keep it separated from Predator
  /// objects.
  /// @details Whenever a boid sees predators near it, an additional component of velocity is evaluated in
  /// order to keep it away from the predators and prevent it from being caught. In particular, the increment
  /// depends on the average of the differences in positions between the boid and the near predators.
  /// @param r Factor which modules the repulsion.
  /// @param near_predators Identifies predators near the boid.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point repel(double r, const std::vector<std::shared_ptr<Bird>> &near_predators) const;
};

class Predator final : public Bird {
 public:
  ///@brief Default constructor.
  Predator();

  /// @brief Construct a new Predator object, with given position and velocity.
  /// @param pos Is the position of the Predator object.
  /// @param vel Is the velocity of the Predator object.
  Predator(point::Point const &pos, point::Point const &vel);

  /// @brief Updates the speed of the Predator object by imposing a maximum speed.
  /// @details If the speed of the predator exceeds the maximum allowed, its module is normalized, leaving the
  /// direction unchanged.
  /// @param p_max_speed Is the maximum speed for Predator objects.
  /// @param velocity Is the velocity to update.
  void friction(double p_max_speed, point::Point &velocity) override;

  /// @brief Updates the speed of the Predator object by imposing a minimum speed.
  /// @details If the speed of the predator exceeds the minimum allowed, its module would be normalized, leaving
  /// the direction unchanged.
  /// @param p_min_speed Is the minimum speed for Predator objects.
  /// @param velocity Is the velocity to update.
  void boost(double p_min_speed, point::Point &velocity) override;

  /// @brief Evaluate the correction to the velocity of the Predator object, in order to chase the near Boid objects.
  /// @details Whenever a predator sees boids near it, an additional component of velocity is evaluated so
  /// that the predator begin to chase them. In particular, the increment depends on the average of the
  /// differences in positions between the predator and the near boids.
  /// @param c Factor which modules the correction.
  /// @param near_boids Identifies the boids near the predator.
  /// @return The correction to the velocity.
  [[nodiscard]] point::Point chase(double c, const std::vector<std::shared_ptr<Bird>> &near_boids) const;
};
}  // namespace bird
#endif