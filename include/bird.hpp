#ifndef BIRD_HPP
#define BIRD_HPP

#include <memory>
#include <vector>

#include "../include/point.hpp"
using namespace point;

namespace bird {

class Bird {
 protected:
  Point position_;
  Point velocity_;
  double sightAngle_{};

 public:
  Bird() = default;
  Bird(Point const &, Point const &);

  virtual Point getPosition() const;
  virtual Point getVelocity() const;

  virtual void setBird(Point, Point);

  virtual Point border(double, double);
  virtual Point separation(double, double, std::vector<std::shared_ptr<Bird>> &);

  virtual void friction(const double[2], Point &) = 0;
  virtual void boost(const double[2], Point &) = 0;

  virtual ~Bird();
};

class Boid final : public Bird {
 public:
  Boid();
  Boid(Point const &, Point const &);

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
}  // namespace bird
#endif