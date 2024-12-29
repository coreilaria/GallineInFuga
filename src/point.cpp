#include "../include/point.hpp"

#include <cmath>

Point::Point() : x_{0.}, y_{0.} {};
Point::Point(const double x, const double y) : x_{x}, y_{y} {};

double Point::get_x() const { return x_; };
double Point::get_y() const { return y_; };

double Point::module() const { return std::sqrt(x_ * x_ + y_ * y_); };
double Point::distance(const Point& P) const {
  return std::sqrt((x_ - P.get_x()) * (x_ - P.get_x()) + (y_ - P.get_y()) * (y_ - P.get_y()));
};

float Point::angle() const { return static_cast<float>(std::atan2(y_, x_) + M_PI / 2); };
// std::atan2 tiene conto dei segni di velocity.x e velocity.y e fornisce il risultato corretto in radianti.

Point& Point::operator+=(const Point& a) {
  x_ += a.get_x();
  y_ += a.get_y();
  return *this;
}

Point operator+(const Point& a, const Point& b) {
  const Point sum{a.get_x() + b.get_x(), a.get_y() + b.get_y()};
  return sum;
};

Point operator-(const Point& a, const Point& b) {
  const Point diff{a.get_x() - b.get_x(), a.get_y() - b.get_y()};
  return diff;
};

Point operator*(const double scalar, const Point& a) {
  const Point mult{scalar * a.get_x(), scalar * a.get_y()};
  return mult;
};

Point operator/(const Point& a,
                const double scalar) {  // aggiungere assert scalar !=0
  const Point div{a.get_x() / scalar, a.get_y() / scalar};
  return div;
};

sf::Vertex Point::operator()() const {
  sf::Vertex out = {sf::Vector2f(static_cast<float>(x_), static_cast<float>(y_))};
  out.color = sf::Color::White;

  return out;
};
