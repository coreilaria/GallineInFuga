#ifndef BIRD_HPP
#define BIRD_HPP

#include <memory>
#include <vector>

#include "../include/point.hpp"

class Bird {
 protected:
  Point position_;
  Point velocity_;

 public:
  Bird();
  Bird(Point const &, Point const &);

  virtual Point get_position() const;
  virtual Point get_velocity() const;

  virtual void set_position(Point);
  virtual void set_velocity(Point);

  virtual void friction(double, Point &);
  virtual void boost(double, Point &);
  virtual Point border(double, double, Point);
  // virtual void rotateTriangle(sf::VertexArray &, double) ;

  virtual Point separation(double, double, std::vector<std::shared_ptr<Bird>> &) = 0;

  virtual ~Bird();
};

class Boid final : public Bird {
 public:
  Boid();
  Boid(Point const &, Point const &);  // dentro chiama Bird()

  Point separation(double, double, std::vector<std::shared_ptr<Bird>> &) override;
  Point alignment(double, std::vector<std::shared_ptr<Bird>> &) const;
  Point cohesion(double, std::vector<std::shared_ptr<Bird>> &) const;
};

class Predator final : public Bird {
 public:
  Predator();
  Predator(Point const &, Point const &);
  Point separation(double, double, std::vector<std::shared_ptr<Bird>> &) override;
};

#endif