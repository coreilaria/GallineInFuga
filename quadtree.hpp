#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>

#include "point.hpp"

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

  Rectangle& operator=(const Rectangle&);
};

class QuadTree {
 private:
  Rectangle boundary_;
  double capacity_;
  std::vector<Point> points_;
  bool divided_;

 public:
  QuadTree(Rectangle, double);
  void insert(
      Point);  // ricordarsi che poi sarà Boid::position_ il Point da inserire
  void subdivide();
};

#endif