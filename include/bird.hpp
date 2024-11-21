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

  virtual void friction(const double, Point &);
  virtual void boost(const double, Point &);
  virtual Point border(const double, const double, Point);
  // virtual void rotateTriangle(sf::VertexArray &, double) ;

  virtual Point separation(const double, const double, std::vector<std::shared_ptr<Bird>> &) = 0;

  virtual ~Bird();
};

class Boid : public Bird {
 public:
  Boid();
  Boid(Point const &, Point const &);  // dentro chiama Bird()

  Point separation(const double, const double, std::vector<std::shared_ptr<Bird>> &) override;
  Point alignment(const double, std::vector<std::shared_ptr<Bird>> &);
  Point cohesion(const double, std::vector<std::shared_ptr<Bird>> &);
};

class Predator : public Bird {
 public:
  Predator();
  Predator(Point const &, Point const &);
  Point separation(const double, const double, std::vector<std::shared_ptr<Bird>> &) override;
};

#endif