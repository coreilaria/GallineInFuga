#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

class Point {
 private:
  double x_;
  double y_;

 public:
  Point();
  Point(double, double);

  double get_x() const;
  double get_y() const;
  double module() const;
  double distance(const Point&) const;
  float angle() const;

  // Point& operator=(const Point& p);
  Point& operator+=(const Point&);
  sf::Vertex operator()() const;

};

Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);
Point operator*(double, const Point&);
Point operator/(const Point&, double);


#endif