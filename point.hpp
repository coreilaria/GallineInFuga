#ifndef POINT_HPP
#define POINT_HPP

class Point{
private:
double m_x;
double m_y;

public:
Point();
Point(double, double);
double distance() const;
double get_x() const;
double get_y() const;

};
Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);
Point operator*(const double, const Point&);

#endif