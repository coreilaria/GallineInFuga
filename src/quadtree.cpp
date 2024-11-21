#include "../include/quadtree.hpp"

#include <cmath>

#include "../include/bird.hpp"

Rectangle::Rectangle(Point center, double width, double height)
    : center_{center.get_x(), center.get_y()},
      // : center_= center,
      width_{width}, height_{height} {};

Rectangle::Rectangle(double x, double y, double w, double h) : center_{x, y}, width_{w}, height_{h} {};

double Rectangle::get_width() const { return width_; };
double Rectangle::get_height() const { return height_; };

double Rectangle::get_xcenter() const { return center_.get_x(); };  // forse non serve
double Rectangle::get_ycenter() const { return center_.get_y(); };  // forse non serve

Point Rectangle::get_center() const {
  Point p{center_.get_x(), center_.get_y()};
  return p;
};

bool Rectangle::contains(Point p) {
  return (std::abs(p.get_x() - center_.get_x()) <= width_ && std::abs(p.get_y() - center_.get_y()) <= height_);
}

// Rectangle& Rectangle::operator=(const Rectangle& r) {
//   if (this != &r) {  // Evita l'autoassegnamento
//     center_ = r.get_center();
//     width_ = r.get_width();
//     height_ = r.get_height();
//   }
//   return *this;
// };

QuadTree::QuadTree(Rectangle boundary, double capacity)
    : boundary_{boundary.get_center(), boundary.get_width(), boundary.get_height()}, capacity_{capacity}, boids_{},
      divided_{false} {};

bool QuadTree::insert(Boid* b) {
  // checking whether the point is within the boundary
  if (!boundary_.contains(b->get_position())) return false;

  // controllare se necessario static cast unsignint->int
  if (boids_.size() <= capacity_) {
    boids_.push_back(b);
    return true;

  } else {
    if (!divided_) subdivide();

    // Inserting the boid in one of the children QuadTrees, depending on his
    // position within the previous boundary
    return (northwest->insert(b)) || (northeast->insert(b)) || (southeast->insert(b)) || (southwest->insert(b));
  }
}

;

void QuadTree::subdivide() {
  double x = boundary_.get_xcenter();  // pensare se questi metodi ci servano davvero
  double y = boundary_.get_ycenter();
  double w = boundary_.get_width();
  double h = boundary_.get_height();

  Rectangle nw{x - w / 2, y + h / 2, w / 2, h / 2};
  northwest = new QuadTree{nw, capacity_};

  Rectangle ne{x + w / 2, y + h / 2, w / 2, h / 2};
  northeast = new QuadTree{ne, capacity_};

  Rectangle se{x + w / 2, y - h / 2, w / 2, h / 2};
  southeast = new QuadTree{se, capacity_};

  Rectangle sw{x - w / 2, y - h / 2, w / 2, h / 2};
  southwest = new QuadTree{sw, capacity_};

  divided_ = true;
}
