#include "boid.hpp"
#include "point.hpp"

Boid::Boid(): position_{0., 0.}, velocity_{0., 0.} {};
Boid::Boid(Point const& pos, Point const& vel): position_{pos}, velocity_{vel} {};

Point Boid::separation(double s, Point p){

} ;
Point Boid::alignment(double a){
    
} ;
Point Boid::cohesion(double c){
    
} ;

void Boid::addBoid(Point const& p, Point const& v){
Boid *b = new Boid(p, v);
flock_.push_back(b);
//remember to add destructor for flock vector elements/ delete
};


void Boid::update(){
    
} ;