#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <vector>

#include "../doctest.h"
#include "../include/bird.hpp"
#include "../include/point.hpp"
#include "../include/flock.hpp"

constexpr double d {80.};
constexpr double ds {d/2.};
constexpr double s {0.6};
constexpr double c {0.001};
constexpr double a {0.6};

constexpr double maxSpeed[2]{5., 4.};
constexpr double minSpeed[2]{3., 2.};

TEST_CASE("Testing Point class") {
  Point p0;
  Point p1(1., 1.);
  Point p2(-5.2, 3.75);
  Point p3(-2., -4.);
  Point p4(1., -6.);

  double scalar0 = 0.;
  double scalar1 = 7.;
  double scalar2 = -11.;

//Messe parentesi () nelle condizioni per evitare che il compilatore interpreti erroneamente << prima di ==
  SUBCASE("Testing getters") {
    CHECK((p0.get_x() == 0.));
    CHECK((p0.get_y() == 0.));
    CHECK((p1.get_x() == 1.));
    CHECK((p1.get_y() == 1.));
  }
  SUBCASE("Testing module method") {
    CHECK((p0.module() == 0));
    CHECK((p1.module() == doctest::Approx(1.41421356)));
    CHECK((p2.module() == doctest::Approx(6.41112315)));
  }
  SUBCASE("Testing distance method") {
    CHECK((p0.distance(p1) == doctest::Approx(1.41421356)));
    CHECK((p0.distance(p2) == doctest::Approx(6.41112315)));

    CHECK((p1.distance(p0) == doctest::Approx(1.41421356)));
    CHECK((p1.distance(p2) == doctest::Approx(6.78251428)));

    CHECK((p2.distance(p0) == doctest::Approx(6.41112315)));
    CHECK((p2.distance(p1) == doctest::Approx(6.78251428)));
  }

  SUBCASE("Testing angle method") {
    CHECK((p1.angle() == doctest::Approx(3./4 * M_PI)));
    CHECK((p2.angle() == doctest::Approx(3./2 * M_PI - 0.9460137803)));
    CHECK((p3.angle() == doctest::Approx(2 * M_PI - 1.1071487178)));
    CHECK((p4.angle() == doctest::Approx(M_PI/2. - 1.4056476494)));
  }

  SUBCASE("Testing operator +") {
    Point sum1 = p0 + p1;
    Point sum2 = p1 + p0;

    Point sum3 = p1 + p2;
    Point sum4 = p2 + p1;

    CHECK((sum1.get_x() == doctest::Approx(1.)));
    CHECK((sum1.get_y() == doctest::Approx(1.)));

    CHECK((sum2.get_x() == doctest::Approx(1.)));
    CHECK((sum2.get_y() == doctest::Approx(1.)));

    CHECK((sum3.get_x() == doctest::Approx(-4.2)));
    CHECK((sum3.get_y() == doctest::Approx(4.75)));

    CHECK((sum4.get_x() == doctest::Approx(-4.2)));
    CHECK((sum4.get_y() == doctest::Approx(4.75)));
  }

  SUBCASE("Testing operator -") {
    Point diff1 = p0 - p1;
    Point diff2 = p1 - p0;

    Point diff3 = p1 - p2;
    Point diff4 = p2 - p1;

    Point diff5 = p2 - p0;
    Point diff6 = p0 - p2;

    CHECK((diff1.get_x() == doctest::Approx(-1.)));
    CHECK((diff1.get_y() == doctest::Approx(-1.)));

    CHECK((diff2.get_x() == doctest::Approx(1.)));
    CHECK((diff2.get_y() == doctest::Approx(1.)));

    CHECK((diff3.get_x() == doctest::Approx(6.2)));
    CHECK((diff3.get_y() == doctest::Approx(-2.75)));

    CHECK((diff4.get_x() == doctest::Approx(-6.2)));
    CHECK((diff4.get_y() == doctest::Approx(2.75)));

    CHECK((diff5.get_x() == doctest::Approx(-5.2)));
    CHECK((diff5.get_y() == doctest::Approx(3.75)));

    CHECK((diff6.get_x() == doctest::Approx(5.2)));
    CHECK((diff6.get_y() == doctest::Approx(-3.75)));
  }

  SUBCASE("Testing operator *") {
    Point prod1 = scalar0 * p0;
    Point prod2 = scalar0 * p1;
    Point prod3 = scalar0 * p2;

    Point prod4 = scalar1 * p0;
    Point prod5 = scalar1 * p1;
    Point prod6 = scalar1 * p2;

    Point prod7 = scalar2 * p0;
    Point prod8 = scalar2 * p1;
    Point prod9 = scalar2 * p2;

    CHECK((prod1.get_x() == doctest::Approx(0.)));
    CHECK((prod1.get_y() == doctest::Approx(0.)));

    CHECK((prod2.get_x() == doctest::Approx(0.)));
    CHECK((prod2.get_y() == doctest::Approx(0.)));

    CHECK((prod3.get_x() == doctest::Approx(0.)));
    CHECK((prod3.get_y() == doctest::Approx(0.)));

    CHECK((prod4.get_x() == doctest::Approx(0.)));
    CHECK((prod4.get_y() == doctest::Approx(0.)));

    CHECK((prod5.get_x() == doctest::Approx(7.)));
    CHECK((prod5.get_y() == doctest::Approx(7.)));

    CHECK((prod6.get_x() == doctest::Approx(-36.4)));
    CHECK((prod6.get_y() == doctest::Approx(26.25)));

    CHECK((prod7.get_x() == doctest::Approx(0.)));
    CHECK((prod7.get_y() == doctest::Approx(0.)));

    CHECK((prod8.get_x() == doctest::Approx(-11.)));
    CHECK((prod8.get_y() == doctest::Approx(-11.)));

    CHECK((prod9.get_x() == doctest::Approx(57.2)));
    CHECK((prod9.get_y() == doctest::Approx(-41.25)));
  }

  SUBCASE("Testing operator /") {
    Point div2 = p1 / scalar1;
    Point div3 = p1 / scalar2;
    Point div4 = p0 / scalar1;
    Point div5 = p2 / scalar1;
    Point div6 = p2 / scalar2;

    CHECK((div2.get_x() == doctest::Approx(0.142857)));
    CHECK((div2.get_y() == doctest::Approx(0.142857)));

    CHECK((div3.get_x() == doctest::Approx(-0.090909090)));
    CHECK((div3.get_y() == doctest::Approx(-0.090909090)));

    CHECK((div4.get_x() == doctest::Approx(0.)));
    CHECK((div4.get_y() == doctest::Approx(0.)));

    CHECK((div5.get_x() == doctest::Approx(-0.742857)));
    CHECK((div5.get_y() == doctest::Approx(0.535714)));

    CHECK((div6.get_x() == doctest::Approx(0.472727)));
    CHECK((div6.get_y() == doctest::Approx(-0.340909090)));
  }
  SUBCASE("Testing operator +=") {
    Point start0 = p0;
    Point start1(8., -6.);

    start0 += p1;
    start1 += p2;

    CHECK((start0.get_x() == doctest::Approx(1.)));
    CHECK((start0.get_y() == doctest::Approx(1.)));

    CHECK((start1.get_x() == doctest::Approx(2.8)));
    CHECK((start1.get_y() == doctest::Approx(-2.25)));
  }

  SUBCASE("Testing operator ()") {
    sf::Vertex v0, v1, v2;
    v0 = p0();
    v1 = p1();
    v2 = p2();

    CHECK((v0.position.x == doctest::Approx(p0.get_x())));
    CHECK((v0.position.y == doctest::Approx(p0.get_y())));

    CHECK((v1.position.x == doctest::Approx(p1.get_x())));
    CHECK((v1.position.y == doctest::Approx(p1.get_y())));

    CHECK((v2.position.x == doctest::Approx(p2.get_x())));
    CHECK((v2.position.y == doctest::Approx(p2.get_y())));
  }
};


TEST_CASE("Testing Boid class") {

  Point pos1(3., -2.);
  Point vel1(5., -1.);

  double x = pos1.get_x();
  double y = pos1.get_y();

  Point pos2 = pos1 + 0.8 * d * Point(std::cos( M_PI/3. + vel1.angle()), std::sin( M_PI/3. + vel1.angle()));
  Point vel2(-8.5, -6.);

  Point pos3 = pos1 + 0.8 * d * Point(std::cos(-1 * M_PI/3. + vel1.angle()), std::sin( -1 * M_PI/3. + vel1.angle()));
  Point vel3(-7.3, 2.5);

  Point pos4 = pos1 + 0.5 * ds * Point(std::cos(M_PI/3. + vel1.angle()), std::sin(M_PI/3. + vel1.angle()));
  Point vel4(-1., -2.);

  Point pos5 = pos1 + 0.5 * ds * Point(std::cos(-1 * M_PI/3. + vel1.angle()), std::sin( -1 * M_PI/3. + vel1.angle()));
  Point vel5(-5., -3.2);

  Boid b0;
  Boid b1(pos1, vel1);
  Boid b2(pos2, vel2);
  Boid b3(pos3, vel3);
  Boid b4(pos4, vel4);
  Boid b5(pos5, vel5);

  std::vector<std::shared_ptr<Bird>> near_b1 {std::make_shared<Boid>(b2), std::make_shared<Boid>(b3),
      std::make_shared<Boid>(b4), std::make_shared<Boid>(b5)};

  SUBCASE("Testing getters") {
    CHECK((b0.get_position().get_x() == 0.));
    CHECK((b0.get_position().get_y() == 0.));
    CHECK((b0.get_velocity().get_x() == 0.));
    CHECK((b0.get_velocity().get_y() == 0.));

    CHECK((b1.get_position().get_x() == 3.));
    CHECK((b1.get_position().get_y() == -2.));
    CHECK((b1.get_velocity().get_x() == 5.));
    CHECK((b1.get_velocity().get_y() == -1.));
  }

  SUBCASE("Testing separation method") {
    double sep1_x = -s * 0.5 * ds * (std::cos(M_PI/3. + vel1.angle()) + std::cos(-1 * M_PI/3. + vel1.angle()));
    double sep1_y = -s * 0.5 * ds * (std::sin(M_PI/3. + vel1.angle()) + std::sin(-1 * M_PI/3. + vel1.angle()));

    CHECK((b1.separation(s, ds, near_b1).get_x() == doctest::Approx(sep1_x)));
    CHECK((b1.separation(s, ds, near_b1).get_y() == doctest::Approx(sep1_y)));
  }

  SUBCASE("Testing cohesion method") {
    double coh1_x = c * ((4* x +( 0.5 * ds + 0.8 * d)*( std::cos(M_PI/3. + vel1.angle()) + std::cos(-1 * M_PI/3. + vel1.angle())) )/4. - x);
    double coh1_y = c * ((4* y +( 0.5 * ds + 0.8 * d)*( std::sin(M_PI/3. + vel1.angle()) + std::sin(-1 * M_PI/3. + vel1.angle())) )/4. - y);

    CHECK((b1.cohesion(c, near_b1).get_x() == doctest::Approx(coh1_x)));
    CHECK((b1.cohesion(c, near_b1).get_y() == doctest::Approx(coh1_y)));
  }

  SUBCASE("Testing alignment method") {
     double al1_x = a * ((b2.get_velocity().get_x() + b3.get_velocity().get_x() + b4.get_velocity().get_x() + b5.get_velocity().get_x()) / 4. -
                 b1.get_velocity().get_x());

     double al1_y = a * ((b2.get_velocity().get_y() + b3.get_velocity().get_y() + b4.get_velocity().get_y() +  b5.get_velocity().get_y()) / 4. -
                 b1.get_velocity().get_y());

    CHECK((b1.alignment(a, near_b1).get_x() == doctest::Approx(al1_x)));
    CHECK((b1.alignment(a, near_b1).get_y() == doctest::Approx(al1_y)));
  }

  SUBCASE("Testing repel method") {
    //anche se la funzione è pensata per essere usata sui predatori, usiamo il vettore di boid vicini

    double rep1_x = -s * 6 * (0.5 * ds + 0.8 * d ) * (std::cos(M_PI/3. + vel1.angle()) + std::cos(-1 * M_PI/3. + vel1.angle()));
    double rep1_y = -s * 6 * (0.5 * ds + 0.8 * d ) * (std::sin(M_PI/3. + vel1.angle()) + std::sin(-1 * M_PI/3. + vel1.angle()));

    CHECK((b1.repel(s, near_b1).get_x() == doctest::Approx(rep1_x)));
    CHECK((b1.alignment(s, near_b1).get_y() == doctest::Approx(rep1_y)));
  }

    Point v1 = vel1;
    Point v2 = vel2;
    Point v3 = vel3;
    Point v4 = vel4;
    Point v5 = vel5;

  SUBCASE("Testing friction method"){
    b1.friction(maxSpeed, v1);
    b2.friction(maxSpeed, v2);
    b3.friction(maxSpeed, v3);
    b4.friction(maxSpeed, v4);
    b5.friction(maxSpeed, v5);

    CHECK((v1.get_x() == doctest::Approx(maxSpeed[0] * std::cos(vel1.angle()))));
    CHECK((v1.get_y() == doctest::Approx(maxSpeed[0] * std::sin(vel1.angle()))));

    CHECK((v2.get_x() == doctest::Approx(maxSpeed[0] * std::cos(vel2.angle()))));
    CHECK((v2.get_y() == doctest::Approx(maxSpeed[0] * std::sin(vel2.angle()))));

    CHECK((v3.get_x() == doctest::Approx(maxSpeed[0] * std::cos(vel3.angle()))));
    CHECK((v3.get_y() == doctest::Approx(maxSpeed[0] * std::sin(vel3.angle()))));

    CHECK((v4.get_x() == doctest::Approx(vel4.get_x())));
    CHECK((v4.get_y() == doctest::Approx(vel4.get_y())));

    CHECK((v5.get_x() == doctest::Approx(maxSpeed[0] * std::cos(vel5.angle()))));
    CHECK((v5.get_y() == doctest::Approx(maxSpeed[0] * std::sin(vel5.angle()))));
  }

  SUBCASE("Testing boost method"){
    b1.boost(maxSpeed, v1);
    b2.boost(maxSpeed, v2);
    b3.boost(maxSpeed, v3);
    b4.boost(maxSpeed, v4);
    b5.boost(maxSpeed, v5);

    CHECK((v1.get_x() == doctest::Approx(vel1.get_x())));
    CHECK((v1.get_y() == doctest::Approx(vel1.get_y())));

    CHECK((v2.get_x() == doctest::Approx(vel2.get_x())));
    CHECK((v2.get_y() == doctest::Approx(vel2.get_y())));

    CHECK((v3.get_x() == doctest::Approx(vel3.get_x())));
    CHECK((v3.get_y() == doctest::Approx(vel3.get_y())));

    CHECK((v4.get_x() == doctest::Approx(minSpeed[0] * std::cos(vel4.angle()))));
    CHECK((v4.get_y() == doctest::Approx(minSpeed[0] * std::sin(vel4.angle()))));

    CHECK((v5.get_x() == doctest::Approx(vel5.get_x())));
    CHECK((v5.get_y() == doctest::Approx(vel5.get_y())));
  }

 };
//
//  TEST_CASE("Testing Predator class") {
//    SUBCASE(""){}
//
//  };
