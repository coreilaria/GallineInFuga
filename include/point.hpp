#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

namespace point {
class Point {
 private:
  double x_;
  double y_;

 public:
  Point();
  Point(double, double);

  double getX() const;
  double getY() const;
  double module() const;
  double distance(const Point&) const;
  float angle() const;

  Point& operator+=(const Point&);
  sf::Vertex operator()() const;
};

Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);
Point operator*(double, const Point&);
Point operator/(const Point&, double);
bool operator==(const Point&, const Point&);
}  // namespace point
#endif