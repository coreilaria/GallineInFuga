/// @file       ../include/point.hpp
/// @brief      Defines the Point class.
///
/// @details    This file contains the definition of Point class.
///             The Point class represents a vector in a two dimension space.
#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

namespace point {
class Point {
  /// @brief The Point class represents a vector in 2D.
  /// @param x_ Is the x component of the vector.
  /// @param y_ Is the y component of the vector.
 private:
  double x_;
  double y_;

 public:
  /// @brief Constructs a new Point object and sets the vector to (0., 0.) as default.
  Point();

  /// @brief Constructs a new Point object, with the two coordinates.
  /// @param x Is the x component of the vector.
  /// @param y Is the y component of the vector.
  Point(double x, double y);

  /// @brief Gets the x coordinate.
  /// @return The x component of the vector.
  [[nodiscard]] double getX() const;

  /// @brief Gets the y coordinate.
  /// @return The y component of the vector.
  [[nodiscard]] double getY() const;

  ///@brief Evaluates the distance of the vector from the origin.
  ///@return The distance from the origin.
  [[nodiscard]] double module() const;

  ///@brief Evaluates the distance between two Point objects.
  ///@param p Is the Point we want to find the distance form.
  ///@return The module of the two vector difference.
  [[nodiscard]] double distance(const Point& p) const;

  ///@brief Evaluates the angle between the vector and the vertical axis.
  ///@return An angle in radiant, in the range [0 - 2pi].
  [[nodiscard]] float angle() const;

  ///@brief Evaluates the sum between itself and another Point object.
  ///@param a Is another Point object.
  ///@return Itself.
  Point& operator+=(const Point& a);

  ///@brief Converts a Point object into a sf::Vertex object.
  ///@return The conversion in sf::Vertex.
  sf::Vertex operator()() const;
};

///@brief Evaluates the sum between two Point objects.
///@param a, b Are the two Point objects to sum.
///@return The vector sum.
Point operator+(const Point& a, const Point& b);

///@brief Evaluates the difference between two Point objects.
///@param a, b Are the two Point object to subtract.
///@return The vector difference.
Point operator-(const Point& a, const Point& b);

///@brief Evaluates the multiplication by a scalar of a Point object.
///@param scalar Is the scalar that we want to multiply for.
///@param a Is a Point object.
///@return The vector whose components are the components of the Point object multiplied by the scalar.
Point operator*(double scalar, const Point& a);

///@brief Evaluates the division by a scalar of Point object.
///@param scalar Is the scalar that we want to divide for.
///@param a Is a Point object.
///@return The vector whose components are the components of the Point object divided by the scalar.
Point operator/(const Point& a, double scalar);

///@brief Compares two Point objects.
///@param a, b Are the Point objects in comparison.
///@return The result of the comparison.
bool operator==(const Point& a, const Point& b);
}  // namespace point
#endif