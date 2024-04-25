#include "boid.hpp"

#include "point.hpp"

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel)
    : position_{pos}, velocity_{vel} {};

void Boid::set_separation(double ds) { d_separation_ = ds; };
void Boid::set_distance(double d) { distance_ = d; };

Point Boid::separation(double s) {
  Point v1{};
  Point v2{};

  for (int i = 0; i < near_.size(); ++i) {
    v2 = {near_[i]->position_.get_x(), near_[i]->position_.get_y()};

    if (v2.distance(position_) < d_separation_) {
      v1 = {v2.get_x() - position_.get_x(), v2.get_y() - position_.get_y()};
      v1 = (1 - s) * v1;
    }
  }
  return v1;
};

Point Boid::alignment(double a) {
  Point v1{};
  Point v2{};
  for (int i = 0; i < near_.size(); ++i) {
    v1 = {near_[i]->velocity_.get_x(), near_[i]->velocity_.get_y()};
    v2 = {v1.get_x() - velocity_.get_x(), v1.get_y() - velocity_.get_y()};
    v2 = (1 - a / (near_.size() - 1)) * v2;
  }
  return v2;
};
Point Boid::cohesion(double c) {
  Point sum{};
  Point v3{};
  for (int i = 0; i < near_.size(); ++i) {
    v3 = {near_[i]->position_.get_x(), near_[i]->position_.get_y()};
    sum = sum + v3;
  }

  return  c * (( sum - position_) / ((near_.size() - 1) * 1.) - position_);
};

void Boid::addBoid(Point const& p, Point const& v) {
  Boid* b = new Boid(p, v);
  flock_.push_back(b);
  // remember to add destructor for flock vector elements/ delete
};

void Boid::update(double s, double a, double c){
    velocity_= velocity_ + separation(s) + alignment(a)+ cohesion(c);
};

void Boid::border (){}; //da IMPLEMENTARE