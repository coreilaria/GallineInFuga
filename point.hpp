#ifndef POINT_HPP
#define POINT_HPP

class Point {
 private:
  double x_;
  double y_;

 public:
  Point();
  Point(double, double);

  double module() const;
  double distance(const Point&) const;
  // double distance(double, double) const;

  double get_x() const;
  double get_y() const;

  // Point& operator=(const Point& p);
  Point& operator+=(const Point&);
};

Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);
Point operator*(const double, const Point&);
Point operator/(const Point&, const double);

#endif