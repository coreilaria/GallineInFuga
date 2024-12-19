#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>

#include "../include/bird.hpp"
#include "../include/point.hpp"

class Rectangle {
 private:
  Point center_;
  double width_;
  double height_;

 public:
  Rectangle(Point, double, double);
  Rectangle(double, double, double, double);

  double get_xcenter() const;
  double get_ycenter() const;
  Point get_center() const;
  double get_width() const;
  double get_height() const;

  bool contains(Point);

  // Rectangle& operator=(const Rectangle&);  Operatore di assegnamento
};

class QuadTree {
 private:
  Rectangle boundary_;
  double capacity_;
  std::vector<Boid*> boids_;
  bool divided_;

 public:
  QuadTree(Rectangle, double);

  QuadTree* northwest;
  QuadTree* northeast;
  QuadTree* southeast;
  QuadTree* southwest;

  bool insert(Boid*);
  // ricordarsi che poi ci serviranno le Boid::positions_ per stimare i near_ e le Boid::velocity_ per le regole di volo

  void subdivide();
};

#endif