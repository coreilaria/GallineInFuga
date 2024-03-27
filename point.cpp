#include "point.hpp"
#include <cmath>

Point::Point(): m_x{0.}, m_y{0.} {};
Point::Point(double x, double y) : m_x{x}, m_y{y} {};

double Point::distance() const{
    return std::sqrt(m_x * m_x + m_y * m_y);
};

double Point::get_x() const {
    return m_x;
};

double Point::get_y() const {
    return m_y;
};

Point operator+(const Point& a, const Point& b ){
Point sum{a.get_x() + b.get_x(), a.get_y() + b.get_y()};
return sum;         
};
Point operator-(const Point& a, const Point& b ){
Point diff{a.get_x() - b.get_x(), a.get_y() - b.get_y()};
return diff;         
};

Point operator*(const double scalar, const Point& a){
Point mult{scalar * a.get_x(), scalar * a.get_y()};
return mult;
};



