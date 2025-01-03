#include "../include/point.hpp"

#include <cassert>
#include <cmath>

namespace point {

Point::Point() : x_{0.}, y_{0.} {}
Point::Point(const double x, const double y) : x_{x}, y_{y} {}

double Point::getX() const { return x_; }
double Point::getY() const { return y_; }

double Point::module() const { return std::sqrt(x_ * x_ + y_ * y_); }
double Point::distance(const Point& p) const {
  return std::sqrt((x_ - p.getX()) * (x_ - p.getX()) + (y_ - p.getY()) * (y_ - p.getY()));
}

float Point::angle() const { return static_cast<float>(std::atan2(y_, x_) + M_PI / 2); }  // output in radiant

Point& Point::operator+=(const Point& a) {
  x_ += a.getX();
  y_ += a.getY();
  return *this;
}

Point operator+(const Point& a, const Point& b) {
  const Point sum{a.getX() + b.getX(), a.getY() + b.getY()};
  return sum;
}

Point operator-(const Point& a, const Point& b) {
  const Point diff{a.getX() - b.getX(), a.getY() - b.getY()};
  return diff;
}

Point operator*(const double scalar, const Point& a) {
  const Point mult{scalar * a.getX(), scalar * a.getY()};
  return mult;
}

Point operator/(const Point& a, const double scalar) {
  assert(scalar != 0);
  const Point div{a.getX() / scalar, a.getY() / scalar};
  return div;
}

bool operator==(const Point& a, const Point& b) { return a.getX() == b.getX() && a.getY() == b.getY(); }

sf::Vertex Point::operator()() const {
  sf::Vertex out = {sf::Vector2f(static_cast<float>(x_), static_cast<float>(y_))};
  out.color = sf::Color::White;
  return out;
}
}  // namespace point
