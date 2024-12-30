#ifndef BIRD_HPP
#define BIRD_HPP

#include <memory>
#include <vector>

#include "../include/point.hpp"

class Bird {
 protected:
  Point position_;
  Point velocity_;
  double sightAngle_{};

 public:
  Bird() = default;
  Bird(Point const &, Point const &);

  virtual Point get_position() const;
  virtual Point get_velocity() const;

  virtual void set_bird(Point, Point);
  // virtual void set_velocity(Point);

  virtual Point border(double, double, Point);
  virtual Point separation(double, double, std::vector<std::shared_ptr<Bird>> &);

  virtual void friction(const double[2], Point &) = 0;
  virtual void boost( const double[2], Point &) = 0;

  virtual ~Bird();
};

class Boid final : public Bird {
 public:
  Boid();
  Boid(Point const &, Point const &);  // dentro chiama Bird()

  void friction(const double[2], Point &) override;
  void boost(const double[2], Point &) override;

  Point alignment(double, std::vector<std::shared_ptr<Bird>> &) const;
  Point cohesion(double, std::vector<std::shared_ptr<Bird>> &) const;
  Point repel(double, std::vector<std::shared_ptr<Bird>> &) const;
};

class Predator final : public Bird {
 public:
  Predator();
  Predator(Point const &, Point const &);

  void friction(const double[2], Point &) override;
  void boost(const double[2], Point &) override;

  Point chase(double, std::vector<std::shared_ptr<Bird>> &) const;
};

#endif