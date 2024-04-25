#include "quadtree.hpp"

#include "boid.hpp"

Rectangle::Rectangle(Point center, double width, double height)
    : center_{center.get_x(), centre.get_y()},
      width_{width},
      height_{height} {};

Rectangle::Rectangle(double x, double y, double w, double h)
    : center_{x, y}, width_{width}, height_{height} {};

double Rectangle::get_width() const { return width_; };
double Rectangle::get_height() const { return height_; };

double Rectangle::get_xcenter() const { center_.get_x(); }; //forse non serve
double Rectangle::get_ycenter() const { center_.get_y(); }; // forse non serve

Point Rectangle::get_center() const {
  Point p{center_.x, center_.y};
  return p;
};

// Operatore di assegnamento
Rectangle& operator=(const Rectangle& r) {
  if (this != &r) {  // Evita l'autoassegnamento
    center_ = r.get_center();
    width_ = r.get_width();
    height_ = r.get_height();
  }
  return *this;
};

QuadTree::QuadTree(Rectangle boundary, double capacity)
    : boundary_ = boundary,
      capacity_ = capacity, divided_{false}, points_{} {};

void QuadTree::insert(Point point) {
  if (points_.size() <= capacity_)
    points_.push_back(point);

  else {
    subdivide();
    divided_ = true;
  }
};

void QuadTree::subdivide() {
  double x = boundary_.get_xcenter();
  double y = boundary_.get_ycenter();
  double w = boundary_.width_;
  double h = boundary_.height_;

  Rectangle nw{x - w / 2, y + h / 2, w / 2, h / 2};
  QuadTree northwest{nw, capacity_};

  Rectangle ne{x + w / 2, y + h / 2, w / 2, h / 2};
  QuadTree northeast{ne, capacity_};

  Rectangle se{x + w / 2, y - h / 2, w / 2, h / 2};
  QuadTree southeast{se, capacity_};

  Rectangle sw{x - w / 2, y - h / 2, w / 2, h / 2};
  QuadTree southwest{sw, capacity_};
}
