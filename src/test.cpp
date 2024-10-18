#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <random>
#include <vector>

#include "../doctest.h"
#include "../include/boid.hpp"
#include "../include/point.hpp"
#include "../include/sfml.hpp"

TEST_CASE("Testing Point class") {
  Point p0;
  Point p1(1., 1.);
  Point p2(-5.2, 3.75);

  double scalar0 = 0.;
  double scalar1 = 7.;
  double scalar2 = -11.;

  SUBCASE("Testing getters") {
    CHECK(p0.get_x() == 0.);
    CHECK(p0.get_y() == 0.);
    CHECK(p1.get_x() == 1.);
    CHECK(p1.get_y() == 1.);
  }
  SUBCASE("Testing module method") {
    CHECK(p0.module() == 0);
    CHECK(p1.module() == doctest::Approx(1.41421356));
    CHECK(p2.module() == doctest::Approx(6.41112315));
  }
  SUBCASE("Testing distance method") {
    CHECK(p0.distance(p1) == doctest::Approx(1.41421356));
    CHECK(p0.distance(p2) == doctest::Approx(6.41112315));

    CHECK(p1.distance(p0) == doctest::Approx(1.41421356));
    CHECK(p1.distance(p2) == doctest::Approx(6.78251428));

    CHECK(p2.distance(p0) == doctest::Approx(6.41112315));
    CHECK(p2.distance(p1) == doctest::Approx(6.78251428));
  }
  SUBCASE("Testing operator +") {
    Point sum1 = p0 + p1;
    Point sum2 = p1 + p0;

    Point sum3 = p1 + p2;
    Point sum4 = p2 + p1;

    CHECK(sum1.get_x() == doctest::Approx(1.));
    CHECK(sum1.get_y() == doctest::Approx(1.));

    CHECK(sum2.get_x() == doctest::Approx(1.));
    CHECK(sum2.get_y() == doctest::Approx(1.));

    CHECK(sum3.get_x() == doctest::Approx(-4.2));
    CHECK(sum3.get_y() == doctest::Approx(4.75));

    CHECK(sum4.get_x() == doctest::Approx(-4.2));
    CHECK(sum4.get_y() == doctest::Approx(4.75));
  }

  SUBCASE("Testing operator -") {
    Point diff1 = p0 - p1;
    Point diff2 = p1 - p0;

    Point diff3 = p1 - p2;
    Point diff4 = p2 - p1;

    Point diff5 = p2 - p0;
    Point diff6 = p0 - p2;

    CHECK(diff1.get_x() == doctest::Approx(-1.));
    CHECK(diff1.get_y() == doctest::Approx(-1.));

    CHECK(diff2.get_x() == doctest::Approx(1.));
    CHECK(diff2.get_y() == doctest::Approx(1.));

    CHECK(diff3.get_x() == doctest::Approx(6.2));
    CHECK(diff3.get_y() == doctest::Approx(-2.75));

    CHECK(diff4.get_x() == doctest::Approx(-6.2));
    CHECK(diff4.get_y() == doctest::Approx(2.75));

    CHECK(diff5.get_x() == doctest::Approx(-5.2));
    CHECK(diff5.get_y() == doctest::Approx(3.75));

    CHECK(diff6.get_x() == doctest::Approx(5.2));
    CHECK(diff6.get_y() == doctest::Approx(-3.75));
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

    CHECK(prod1.get_x() == doctest::Approx(0.));
    CHECK(prod1.get_y() == doctest::Approx(0.));

    CHECK(prod2.get_x() == doctest::Approx(0.));
    CHECK(prod2.get_y() == doctest::Approx(0.));

    CHECK(prod3.get_x() == doctest::Approx(0.));
    CHECK(prod3.get_y() == doctest::Approx(0.));

    CHECK(prod4.get_x() == doctest::Approx(0.));
    CHECK(prod4.get_y() == doctest::Approx(0.));

    CHECK(prod5.get_x() == doctest::Approx(7.));
    CHECK(prod5.get_y() == doctest::Approx(7.));

    CHECK(prod6.get_x() == doctest::Approx(-36.4));
    CHECK(prod6.get_y() == doctest::Approx(26.25));

    CHECK(prod7.get_x() == doctest::Approx(0.));
    CHECK(prod7.get_y() == doctest::Approx(0.));

    CHECK(prod8.get_x() == doctest::Approx(-11.));
    CHECK(prod8.get_y() == doctest::Approx(-11.));

    CHECK(prod9.get_x() == doctest::Approx(57.2));
    CHECK(prod9.get_y() == doctest::Approx(-41.25));
  }

  SUBCASE("Testing operator /") {
    Point div2 = p1 / scalar1;
    Point div3 = p1 / scalar2;
    Point div4 = p0 / scalar1;
    Point div5 = p2 / scalar1;
    Point div6 = p2 / scalar2;

    CHECK(div2.get_x() == doctest::Approx(0.142857));
    CHECK(div2.get_y() == doctest::Approx(0.142857));

    CHECK(div3.get_x() == doctest::Approx(-0.090909090));
    CHECK(div3.get_y() == doctest::Approx(-0.090909090));

    CHECK(div4.get_x() == doctest::Approx(0.));
    CHECK(div4.get_y() == doctest::Approx(0.));

    CHECK(div5.get_x() == doctest::Approx(-0.742857));
    CHECK(div5.get_y() == doctest::Approx(0.535714));

    CHECK(div6.get_x() == doctest::Approx(0.472727));
    CHECK(div6.get_y() == doctest::Approx(-0.340909090));
  }
  SUBCASE("Testing operator +=") {
    Point start0 = p0;
    Point start1(8., -6.);

    start0 += p1;
    start1 += p2;

    CHECK(start0.get_x() == doctest::Approx(1.));
    CHECK(start0.get_y() == doctest::Approx(1.));

    CHECK(start1.get_x() == doctest::Approx(2.8));
    CHECK(start1.get_y() == doctest::Approx(-2.25));
  }

  SUBCASE("Testing operator ()") {
    sf::Vertex v0, v1, v2;
    v0 = p0();
    v1 = p1();
    v2 = p2();

    CHECK(v0.position.x == doctest::Approx(p0.get_x()));
    CHECK(v0.position.y == doctest::Approx(p0.get_y()));

    CHECK(v1.position.x == doctest::Approx(p1.get_x()));
    CHECK(v1.position.y == doctest::Approx(p1.get_y()));

    CHECK(v2.position.x == doctest::Approx(p2.get_x()));
    CHECK(v2.position.y == doctest::Approx(p2.get_y()));
  }
};

TEST_CASE("Testing Boid class") {
  Point poscalar1(3., -2.);
  Point vel1(5., -1.);

  double x = poscalar1.get_x();
  double y = poscalar1.get_y();

  double sep1_x, sep1_y, sep2_x, sep2_y, sep3_x, sep3_y, sep4_x, sep4_y;
  double coh1_x, coh1_y, coh2_x, coh2_y, coh3_x, coh3_y, coh4_x, coh4_y;
  double al1_x, al1_y, al2_x, al2_y, al3_x, al3_y, al4_x, al4_y;

  Point poscalar2(x + ds / 3, y);
  Point vel2(-8.5, -6.);

  Point pos3(x, y + ds / 8);
  Point vel3(-7.3, 2.5);

  Point pos4(
      x + ds / 5 * std::cos(2.),
      y + ds / 5 * std::sin(2.));  // tutti i vicini a b1 sono anche vicini tra loro poichè distano da b1 meno di d/2
  Point vel4(-1., -2.);

  Point pos5(x + 2 * d * std::cos(1.5), y + 2 * d * std::sin(1.5));  // non vicino
  Point vel5(-5., -3.2);

  Boid b0;
  Boid b1(poscalar1, vel1);
  Boid b2(poscalar2, vel2);
  Boid b3(pos3, vel3);
  Boid b4(pos4, vel4);
  Boid b5(pos5, vel5);

  std::vector<Boid> flock{b1, b2, b3, b4, b5};
  std::vector<Boid> near_b1{b2, b3, b4};
  std::vector<Boid> near_b2{b1, b3, b4};
  std::vector<Boid> near_b3{b1, b2, b4};
  std::vector<Boid> near_b4{b1, b2, b3};

  SUBCASE("Testing getters") {
    CHECK(b0.get_position().get_x() == 0.);
    CHECK(b0.get_position().get_y() == 0.);
    CHECK(b0.get_velocity().get_x() == 0.);
    CHECK(b0.get_velocity().get_y() == 0.);

    CHECK(b1.get_position().get_x() == 3.);
    CHECK(b1.get_position().get_y() == -2.);
    CHECK(b1.get_velocity().get_x() == 5.);
    CHECK(b1.get_velocity().get_y() == -1.);
  }

  SUBCASE("Testing separation method") {
    sep1_x = -s * (ds / 3 + ds / 5 * std::cos(2.));
    sep1_y = -s * (ds / 8 + ds / 5 * std::sin(2.));

    sep2_x = -s * (ds / 5 * std::cos(2.) - ds);
    sep2_y = -s * (ds / 5 * std::sin(2.) + ds / 8);

    sep3_x = -s * (ds / 3 + ds / 5 * std::cos(2.));
    sep3_y = -s * (ds / 5 * std::sin(2.) - (3 * ds / 8));

    sep4_x = -s * (ds / 3 - (3 * ds / 5 * std::cos(2.)));
    sep4_y = -s * (ds / 8 - (3 * ds / 5 * std::sin(2.)));

    CHECK(b1.separation(flock).get_x() == doctest::Approx(sep1_x));
    CHECK(b1.separation(flock).get_y() == doctest::Approx(sep1_y));

    CHECK(b2.separation(flock).get_x() == doctest::Approx(sep2_x));
    CHECK(b2.separation(flock).get_y() == doctest::Approx(sep2_y));

    CHECK(b3.separation(flock).get_x() == doctest::Approx(sep3_x));
    CHECK(b3.separation(flock).get_y() == doctest::Approx(sep3_y));

    CHECK(b4.separation(flock).get_x() == doctest::Approx(sep4_x));
    CHECK(b4.separation(flock).get_y() == doctest::Approx(sep4_y));

    CHECK(b5.separation(flock).get_x() == doctest::Approx(0.));
    CHECK(b5.separation(flock).get_y() == doctest::Approx(0.));
  }

  SUBCASE("Testing cohesion method") {
    coh1_x = c * ((3 * x + ds / 3 + ds / 5 * std::cos(2.)) / near_b1.size() - x);
    coh1_y = c * ((3 * y + ds / 8 + ds / 5 * std::sin(2.)) / near_b1.size() - y);

    coh2_x = c * ((3 * x + ds / 5 * std::cos(2.)) / near_b2.size() - (x + ds / 3));
    coh2_y = c * ((3 * y + ds / 8 + ds / 5 * std::sin(2.)) / near_b2.size() - y);

    coh3_x = c * ((3 * x + ds / 3 + ds / 5 * std::cos(2.)) / near_b3.size() - x);
    coh3_y = c * ((3 * y + ds / 5 * std::sin(2.)) / near_b3.size() - (y + ds / 8));

    coh4_x = c * ((3 * x + ds / 3) / near_b4.size() - (x + ds / 5 * std::cos(2.)));
    coh4_y = c * ((3 * y + ds / 8) / near_b4.size() - (y + ds / 5 * std::sin(2.)));

    CHECK(b1.cohesion(near_b1).get_x() == doctest::Approx(coh1_x));
    CHECK(b1.cohesion(near_b1).get_y() == doctest::Approx(coh1_y));

    CHECK(b2.cohesion(near_b2).get_x() == doctest::Approx(coh2_x));
    CHECK(b2.cohesion(near_b2).get_y() == doctest::Approx(coh2_y));

    CHECK(b3.cohesion(near_b3).get_x() == doctest::Approx(coh3_x));
    CHECK(b3.cohesion(near_b3).get_y() == doctest::Approx(coh3_y));

    CHECK(b4.cohesion(near_b4).get_x() == doctest::Approx(coh4_x));
    CHECK(b4.cohesion(near_b4).get_y() == doctest::Approx(coh4_y));
  }

  SUBCASE("Testing alignment method") {
    al1_x = a * ((b2.get_velocity().get_x() + b3.get_velocity().get_x() + b4.get_velocity().get_x()) / near_b1.size() -
                 b1.get_velocity().get_x());

    al1_y = a * ((b2.get_velocity().get_y() + b3.get_velocity().get_y() + b4.get_velocity().get_y()) / near_b1.size() -
                 b1.get_velocity().get_y());

    al2_x = a * ((b1.get_velocity().get_x() + b3.get_velocity().get_x() + b4.get_velocity().get_x()) / near_b2.size() -
                 b2.get_velocity().get_x());
    al2_y = a * ((b1.get_velocity().get_y() + b3.get_velocity().get_y() + b4.get_velocity().get_y()) / near_b2.size() -
                 b2.get_velocity().get_y());

    al3_x = a * ((b1.get_velocity().get_x() + b2.get_velocity().get_x() + b4.get_velocity().get_x()) / near_b3.size() -
                 b3.get_velocity().get_x());

    al3_y = a * ((b1.get_velocity().get_y() + b2.get_velocity().get_y() + b4.get_velocity().get_y()) / near_b3.size() -
                 b3.get_velocity().get_y());

    al4_x = a * ((b1.get_velocity().get_x() + b2.get_velocity().get_x() + b3.get_velocity().get_x()) / near_b4.size() -
                 b4.get_velocity().get_x());

    al4_y = a * ((b1.get_velocity().get_y() + b2.get_velocity().get_y() + b3.get_velocity().get_y()) / near_b4.size() -
                 b4.get_velocity().get_y());

    CHECK(b1.alignment(near_b1).get_x() == doctest::Approx(al1_x));
    CHECK(b1.alignment(near_b1).get_y() == doctest::Approx(al1_y));

    CHECK(b2.alignment(near_b2).get_x() == doctest::Approx(al2_x));
    CHECK(b2.alignment(near_b2).get_y() == doctest::Approx(al2_y));

    CHECK(b3.alignment(near_b3).get_x() == doctest::Approx(al3_x));
    CHECK(b3.alignment(near_b3).get_y() == doctest::Approx(al3_y));

    CHECK(b4.alignment(near_b4).get_x() == doctest::Approx(al4_x));
    CHECK(b4.alignment(near_b4).get_y() == doctest::Approx(al4_y));
  }

  SUBCASE("Testing update_boid method") {
    std::vector<Boid> near1, near2, near3, near4;

    Boid u1, u2, u3, u4;
    u1 = flock[0].update_boid(flock, near1);
    u2 = flock[1].update_boid(flock, near2);
    u3 = flock[2].update_boid(flock, near3);
    u4 = flock[3].update_boid(flock, near4);

    CHECK(static_cast<int>(near1.size()) == 3);
    CHECK(static_cast<int>(near2.size()) == 3);
    CHECK(static_cast<int>(near3.size()) == 3);
    CHECK(static_cast<int>(near4.size()) == 3);

    CHECK(u1.get_velocity().get_x() == doctest::Approx(vel1.get_x() + sep1_x + coh1_x + al1_x));
    CHECK(u1.get_velocity().get_y() == doctest::Approx(vel1.get_y() + sep1_y + coh1_y + al1_y));
    CHECK(u1.get_position().get_x() ==
          doctest::Approx(poscalar1.get_x() + dt * (vel1.get_x() + sep1_x + coh1_x + al1_x)));
    CHECK(u1.get_position().get_y() ==
          doctest::Approx(poscalar1.get_y() + dt * (vel1.get_y() + sep1_y + coh1_y + al1_y)));

    CHECK(u2.get_velocity().get_x() == doctest::Approx(vel2.get_x() + sep2_x + coh2_x + al2_x));
    CHECK(u2.get_velocity().get_y() == doctest::Approx(vel2.get_y() + sep2_y + coh2_y + al2_y));
    CHECK(u2.get_position().get_x() ==
          doctest::Approx(poscalar2.get_x() + dt * (vel2.get_x() + sep2_x + coh2_x + al2_x)));
    CHECK(u2.get_position().get_y() ==
          doctest::Approx(poscalar2.get_y() + dt * (vel2.get_y() + sep2_y + coh2_y + al2_y)));

    CHECK(u3.get_velocity().get_x() == doctest::Approx(vel3.get_x() + sep3_x + coh3_x + al3_x));
    CHECK(u3.get_velocity().get_y() == doctest::Approx(vel3.get_y() + sep3_y + coh3_y + al3_y));
    CHECK(u3.get_position().get_x() == doctest::Approx(pos3.get_x() + dt * (vel3.get_x() + sep3_x + coh3_x + al3_x)));
    CHECK(u3.get_position().get_y() == doctest::Approx(pos3.get_y() + dt * (vel3.get_y() + sep3_y + coh3_y + al3_y)));

    CHECK(u4.get_velocity().get_x() == doctest::Approx(vel4.get_x() + sep4_x + coh4_x + al4_x));
    CHECK(u4.get_velocity().get_y() == doctest::Approx(vel4.get_y() + sep4_y + coh4_y + al4_y));
    CHECK(u4.get_position().get_x() == doctest::Approx(pos4.get_x() + dt * (vel4.get_x() + sep4_x + coh4_x + al4_x)));
    CHECK(u4.get_position().get_y() == doctest::Approx(pos4.get_y() + dt * (vel4.get_y() + sep4_y + coh4_y + al4_y)));
  }

  SUBCASE("Testing evolve method") {
    Boid::evolve(flock);

    CHECK(flock[0].get_velocity().get_x() == doctest::Approx(vel1.get_x() + sep1_x + coh1_x + al1_x));
    CHECK(flock[0].get_velocity().get_y() == doctest::Approx(vel1.get_y() + sep1_y + coh1_y + al1_y));
    CHECK(flock[0].get_position().get_x() ==
          doctest::Approx(poscalar1.get_x() + dt * (vel1.get_x() + sep1_x + coh1_x + al1_x)));
    CHECK(flock[0].get_position().get_y() ==
          doctest::Approx(poscalar1.get_y() + dt * (vel1.get_y() + sep1_y + coh1_y + al1_y)));

    CHECK(flock[1].get_velocity().get_x() == doctest::Approx(vel2.get_x() + sep2_x + coh2_x + al2_x));
    CHECK(flock[1].get_velocity().get_y() == doctest::Approx(vel2.get_y() + sep2_y + coh2_y + al2_y));
    CHECK(flock[1].get_position().get_x() ==
          doctest::Approx(poscalar2.get_x() + dt * (vel2.get_x() + sep2_x + coh2_x + al2_x)));
    CHECK(flock[1].get_position().get_y() ==
          doctest::Approx(poscalar2.get_y() + dt * (vel2.get_y() + sep2_y + coh2_y + al2_y)));

    CHECK(flock[2].get_velocity().get_x() == doctest::Approx(vel3.get_x() + sep3_x + coh3_x + al3_x));
    CHECK(flock[2].get_velocity().get_y() == doctest::Approx(vel3.get_y() + sep3_y + coh3_y + al3_y));
    CHECK(flock[2].get_position().get_x() ==
          doctest::Approx(pos3.get_x() + dt * (vel3.get_x() + sep3_x + coh3_x + al3_x)));
    CHECK(flock[2].get_position().get_y() ==
          doctest::Approx(pos3.get_y() + dt * (vel3.get_y() + sep3_y + coh3_y + al3_y)));

    CHECK(flock[3].get_velocity().get_x() == doctest::Approx(vel4.get_x() + sep4_x + coh4_x + al4_x));
    CHECK(flock[3].get_velocity().get_y() == doctest::Approx(vel4.get_y() + sep4_y + coh4_y + al4_y));
    CHECK(flock[3].get_position().get_x() ==
          doctest::Approx(pos4.get_x() + dt * (vel4.get_x() + sep4_x + coh4_x + al4_x)));
    CHECK(flock[3].get_position().get_y() ==
          doctest::Approx(pos4.get_y() + dt * (vel4.get_y() + sep4_y + coh4_y + al4_y)));

    CHECK(flock[4].get_velocity().get_x() == doctest::Approx(vel5.get_x()));
    CHECK(flock[4].get_velocity().get_y() == doctest::Approx(vel5.get_y()));
    CHECK(flock[4].get_position().get_x() == doctest::Approx(pos5.get_x() + dt * vel5.get_x()));
    CHECK(flock[4].get_position().get_y() == doctest::Approx(pos5.get_y() + dt * vel5.get_y()));
  }
};

TEST_CASE("Testing toSfmlCoord function") {
  sf::Vertex v1{sf::Vector2f(20.f, -35.f)};
  sf::Vertex v2{sf::Vector2f(-5.f, 100.f)};
  sf::Vertex v3{sf::Vector2f(200.f, 15.f)};
  sf::Vertex v4{sf::Vector2f(0.f, 0.f)};
  sf::Vertex v5{sf::Vector2f(static_cast<float>(minPos), static_cast<float>(maxPos))};
  sf::Vertex v6{sf::Vector2f(static_cast<float>(maxPos), static_cast<float>(minPos))};

  toSfmlCoord(v1);
  toSfmlCoord(v2);
  toSfmlCoord(v3);
  toSfmlCoord(v4);
  toSfmlCoord(v5);
  toSfmlCoord(v6);

  CHECK(v1.position.x == doctest::Approx(windowWidth * (20.f / (2 * maxPos) + 0.5)));
  CHECK(v1.position.y == doctest::Approx(windowHeight * (0.5 - (-35.f) / (2 * maxPos))));

  CHECK(v2.position.x == doctest::Approx(windowWidth * ((-5.f) / (2 * maxPos) + 0.5)));
  CHECK(v2.position.y == doctest::Approx(windowHeight * (0.5 - 100.f / (2 * maxPos))));

  CHECK(v3.position.x == doctest::Approx(windowWidth * (200.f / (2 * maxPos) + 0.5)));
  CHECK(v3.position.y == doctest::Approx(windowHeight * (0.5 - 15.f / (2 * maxPos))));

  CHECK(v4.position.x == doctest::Approx(static_cast<float>(windowWidth / 2)));
  CHECK(v4.position.y == doctest::Approx(static_cast<float>(windowHeight / 2)));

  CHECK(v5.position.x == doctest::Approx(0.f));
  CHECK(v5.position.y == doctest::Approx(0.f));

  CHECK(v6.position.x == doctest::Approx(static_cast<float>(windowWidth)));
  CHECK(v6.position.y == doctest::Approx(static_cast<float>(windowHeight)));
}
