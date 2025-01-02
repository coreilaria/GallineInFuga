#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <vector>

#include "../doctest.h"
#include "../include/bird.hpp"
#include "../include/flock.hpp"
#include "../include/graphic.hpp"
#include "../include/point.hpp"

using namespace point;
using namespace bird;
using namespace flock;
using namespace statistics;

constexpr double d{80.};
constexpr double ds{d / 2.};
constexpr double s{0.6};
constexpr double c{0.001};
constexpr double a{0.6};

constexpr double maxSpeed[2]{5., 4.};
constexpr double minSpeed[2]{3., 2.5};

//======================================================================================================================
//===TESTING POINT CLASS================================================================================================
//======================================================================================================================

TEST_CASE("Testing Point class") {
  Point p0;
  Point p1(1., 1.);
  Point p2(-5.2, 3.75);
  Point p3(-2., -4.);
  Point p4(1., -6.);

  double scalar1 = 7.;
  double scalar2 = -11.;

  SUBCASE("Testing getters") {
    CHECK(p0 == Point(0., 0.));
    CHECK(p1 == Point(1., 1.));
  }
  SUBCASE("Testing module method") {
    CHECK(p0.module() == 0.);
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

  SUBCASE("Testing angle method") {
    CHECK(p1.angle() == doctest::Approx(3. / 4 * M_PI));
    CHECK(p2.angle() == doctest::Approx(3. / 2 * M_PI - 0.62478254650161));
    CHECK(p3.angle() == doctest::Approx(-0.463647609));
    CHECK(p4.angle() == doctest::Approx(0.165148675));
  }

  SUBCASE("Testing operator +") {
    Point sum1 = p0 + p1;
    Point sum2 = p1 + p0;

    Point sum3 = p1 + p2;
    Point sum4 = p2 + p1;

    CHECK(sum1 == Point(1., 1.));
    CHECK(sum2 == Point(1., 1.));
    CHECK(sum3 == Point(-4.2, 4.75));
    CHECK(sum4 == Point(-4.2, 4.75));
  }

  SUBCASE("Testing operator -") {
    Point diff1 = p0 - p1;
    Point diff2 = p1 - p0;

    Point diff3 = p1 - p2;
    Point diff4 = p2 - p1;

    Point diff5 = p2 - p0;
    Point diff6 = p0 - p2;

    CHECK(diff1 == Point(-1., -1));
    CHECK(diff2 == Point(1., 1.));
    CHECK(diff3 == Point(6.2, -2.75));
    CHECK(diff4 == Point(-6.2, 2.75));
    CHECK(diff5 == Point(-5.2, 3.75));
    CHECK(diff6 == Point(5.2, -3.75));
  }

  SUBCASE("Testing operator *") {
    double scalar0 = 0.;
    Point prod1 = scalar0 * p0;
    Point prod2 = scalar0 * p1;
    Point prod3 = scalar0 * p2;

    Point prod4 = scalar1 * p0;
    Point prod5 = scalar1 * p1;
    Point prod6 = scalar1 * p2;

    Point prod7 = scalar2 * p0;
    Point prod8 = scalar2 * p1;
    Point prod9 = scalar2 * p2;

    CHECK(prod1 == Point(0., 0.));
    CHECK(prod2 == Point(0., 0.));
    CHECK(prod3 == Point(0., 0.));
    CHECK(prod4 == Point(0., 0.));
    CHECK(prod5 == Point(7., 7.));
    CHECK(prod6 == Point(-36.4, 26.25));
    CHECK(prod7 == Point(0., 0.));
    CHECK(prod8 == Point(-11., -11.));
    CHECK(prod9 == Point(57.2, -41.25));
  }

  SUBCASE("Testing operator /") {
    Point div2 = p1 / scalar1;
    Point div3 = p1 / scalar2;
    Point div4 = p0 / scalar1;
    Point div5 = p2 / scalar1;
    Point div6 = p2 / scalar2;

    CHECK(div2.getX() == doctest::Approx(0.142857));
    CHECK(div2.getY() == doctest::Approx(0.142857));

    CHECK(div3.getX() == doctest::Approx(-0.090909090));
    CHECK(div3.getY() == doctest::Approx(-0.090909090));

    CHECK(div4 == Point(0., 0.));

    CHECK(div5.getX() == doctest::Approx(-0.742857));
    CHECK(div5.getY() == doctest::Approx(0.535714));

    CHECK(div6.getX() == doctest::Approx(0.472727));
    CHECK(div6.getY() == doctest::Approx(-0.340909090));
  }
  SUBCASE("Testing operator +=") {
    Point start0 = p0;
    Point start1(8., -6.);

    start0 += p1;
    start1 += p2;

    CHECK(start0 == Point(1., 1.));
    CHECK(start1 == Point(2.8, -2.25));
  }
  SUBCASE("Testing operator ==") {
    Point point0 = p0;
    Point point1 = p1;
    Point point2 = p2;

    CHECK(point0 == p0);
    CHECK(point1 == p1);
    CHECK(point2 == p2);

    CHECK(!(point0 == p1));
    CHECK(!(point1 == p2));
    CHECK(!(point2 == p1));
  }

  SUBCASE("Testing operator ()") {
    sf::Vertex v0, v1, v2;
    v0 = p0();
    v1 = p1();
    v2 = p2();

    CHECK(v0.position.x == doctest::Approx(0.));
    CHECK(v0.position.y == doctest::Approx(0.));

    CHECK(v1.position.x == doctest::Approx(1.));
    CHECK(v1.position.y == doctest::Approx(1.));

    CHECK(v2.position.x == doctest::Approx(-5.2));
    CHECK(v2.position.y == doctest::Approx(3.75));
  }
}

//======================================================================================================================
//===TESTING BOID CLASS=================================================================================================
//======================================================================================================================

Point pos1(3., -2.);
Point vel1(5., -1.);
double alfa{M_PI / 3. + vel1.angle()};
double beta{-1 * M_PI / 3. + vel1.angle()};

Point pos2 = pos1 + 0.8 * d * Point(std::sin(alfa), -std::cos(alfa));
Point vel2(-8.5, -6.);

Point pos3 = pos1 + 0.8 * d * Point(std::sin(beta), -std::cos(beta));
Point vel3(-7.3, 2.5);

Point pos4 = pos1 + 0.5 * ds * Point(std::sin(alfa), -std::cos(alfa));
Point vel4(-1., -2.);

Point pos5 = pos1 + 0.5 * ds * Point(std::sin(beta), -std::cos(beta));
Point vel5(-5., -3.2);

TEST_CASE("Testing Boid class") {
  double x = pos1.getX();
  double y = pos1.getY();

  Boid b1(pos1, vel1);
  Boid b2(pos2, vel2);
  Boid b3(pos3, vel3);
  Boid b4(pos4, vel4);
  Boid b5;

  b5.setBird(pos5, vel5);

  Point v1 = vel1;
  Point v2 = vel2;
  Point v3 = vel3;
  Point v4 = vel4;
  Point v5 = vel5;

  std::vector<std::shared_ptr<Bird>> near_b1{std::make_shared<Boid>(b2), std::make_shared<Boid>(b3),
                                             std::make_shared<Boid>(b4), std::make_shared<Boid>(b5)};

  SUBCASE("Testing getters") {
    Boid b0;
    CHECK(b0.getPosition() == Point(0., 0.));
    CHECK(b0.getVelocity() == Point(0., 0.));

    CHECK(b1.getPosition() == Point(3., -2.));
    CHECK(b1.getVelocity() == Point(5., -1.));
  }

  SUBCASE("Testing setters") {
    CHECK(b5.getPosition().getX() == doctest::Approx(pos5.getX()));
    CHECK(b5.getPosition().getY() == doctest::Approx(pos5.getY()));

    CHECK(b5.getVelocity() == Point(-5., -3.2));
  }

  SUBCASE("Testing separation method") {
    double sep1_x = -s * 0.5 * ds * (std::sin(alfa) + std::sin(beta));
    double sep1_y = -s * 0.5 * ds * -(std::cos(alfa) + std::cos(beta));

    CHECK(b1.separation(s, ds, near_b1).getX() == doctest::Approx(sep1_x));
    CHECK(b1.separation(s, ds, near_b1).getY() == doctest::Approx(sep1_y));
  }

  SUBCASE("Testing cohesion method") {
    double coh1_x = c * ((4 * x + (0.5 * ds + 0.8 * d) * (std::sin(alfa) + std::sin(beta))) / 4. - x);
    double coh1_y = c * ((4 * y + (0.5 * ds + 0.8 * d) * -(std::cos(alfa) + std::cos(beta))) / 4. - y);

    CHECK(b1.cohesion(c, near_b1).getX() == doctest::Approx(coh1_x));
    CHECK(b1.cohesion(c, near_b1).getY() == doctest::Approx(coh1_y));
  }

  SUBCASE("Testing alignment method") {
    double al1_x = a * ((vel2.getX() + vel3.getX() + vel4.getX() + vel5.getX()) / 4. - 5.);
    double al1_y = a * ((vel2.getY() + vel3.getY() + vel4.getY() + vel5.getY()) / 4. - -1.);

    CHECK(b1.alignment(a, near_b1).getX() == doctest::Approx(al1_x));
    CHECK(b1.alignment(a, near_b1).getY() == doctest::Approx(al1_y));
  }

  SUBCASE("Testing repel method") {
    // here we apply Boid::repel on near_b1, which identifies the boids near b1, even if it was initially intended
    // to be applied on near_predators

    double rep1_x = -s * 6 * (0.5 * ds + 0.8 * d) * (std::sin(alfa) + std::sin(beta));
    double rep1_y = -s * 6 * (0.5 * ds + 0.8 * d) * -(std::cos(alfa) + std::cos(beta));

    CHECK(b1.repel(s, near_b1).getX() == doctest::Approx(rep1_x));
    CHECK(b1.repel(s, near_b1).getY() == doctest::Approx(rep1_y));
  }

  SUBCASE("Testing friction method") {
    b1.friction(maxSpeed, v1);
    b2.friction(maxSpeed, v2);
    b3.friction(maxSpeed, v3);
    b4.friction(maxSpeed, v4);
    b5.friction(maxSpeed, v5);

    CHECK(v1.getX() == doctest::Approx(maxSpeed[0] * std::sin(vel1.angle())));
    CHECK(v1.getY() == doctest::Approx(-maxSpeed[0] * std::cos(vel1.angle())));

    CHECK(v2.getX() == doctest::Approx(maxSpeed[0] * std::sin(vel2.angle())));
    CHECK(v2.getY() == doctest::Approx(-maxSpeed[0] * std::cos(vel2.angle())));

    CHECK(v3.getX() == doctest::Approx(maxSpeed[0] * std::sin(vel3.angle())));
    CHECK(v3.getY() == doctest::Approx(-maxSpeed[0] * std::cos(vel3.angle())));

    CHECK(v4.getX() == doctest::Approx(vel4.getX()));
    CHECK(v4.getY() == doctest::Approx(vel4.getY()));

    CHECK(v5.getX() == doctest::Approx(maxSpeed[0] * std::sin(vel5.angle())));
    CHECK(v5.getY() == doctest::Approx(-maxSpeed[0] * std::cos(vel5.angle())));
  }

  SUBCASE("Testing boost method") {
    b1.boost(minSpeed, v1);
    b2.boost(minSpeed, v2);
    b3.boost(minSpeed, v3);
    b4.boost(minSpeed, v4);
    b5.boost(minSpeed, v5);

    CHECK(v1 == Point(5., -1.));
    CHECK(v2 == Point(-8.5, -6.));
    CHECK(v3 == Point(-7.3, 2.5));

    CHECK(v4.getX() == doctest::Approx(minSpeed[0] * std::sin(vel4.angle())));
    CHECK(v4.getY() == doctest::Approx(-minSpeed[0] * std::cos(vel4.angle())));

    CHECK(v5 == Point(-5., -3.2));
  }
};

//======================================================================================================================
//===TESTING PREDATOR CLASS=============================================================================================
//======================================================================================================================

TEST_CASE("Testing Predator class") {
  Predator p1(pos1, vel1);
  Predator p2(pos2, vel2);
  Predator p3(pos3, vel3);
  Predator p4;

  pos4 = pos1 + 0.5 * d * Point(std::sin(alfa), -std::cos(alfa));
  p4.setBird(pos4, vel4);

  Point v1 = vel1;
  Point v2 = vel2;
  Point v3 = vel3;
  Point v4 = vel4;

  std::vector<std::shared_ptr<Bird>> near_p1{std::make_shared<Predator>(p2), std::make_shared<Predator>(p3),
                                             std::make_shared<Predator>(p4)};

  SUBCASE("Testing getters") {
    Predator p0;
    CHECK(p0.getPosition() == Point(0., 0.));
    CHECK(p0.getVelocity() == Point(0., 0.));
    CHECK(p1.getPosition() == Point(3., -2.));
    CHECK(p1.getVelocity() == Point(5., -1.));
  }

  SUBCASE("Testing setters") {
    CHECK(p2.getPosition().getX() == doctest::Approx(pos2.getX()));
    CHECK(p2.getPosition().getY() == doctest::Approx(pos2.getY()));
    CHECK(p2.getVelocity() == Point(-8.5, -6.));

    CHECK(p3.getPosition().getX() == doctest::Approx(pos3.getX()));
    CHECK(p3.getPosition().getY() == doctest::Approx(pos3.getY()));
    CHECK(p3.getVelocity() == Point(-7.3, 2.5));

    CHECK(p4.getPosition().getX() == doctest::Approx(pos4.getX()));
    CHECK(p4.getPosition().getY() == doctest::Approx(pos4.getY()));
    CHECK(p4.getVelocity() == Point(-1., -2.));
  }

  SUBCASE("Testing chase method") {
    // here we apply Predator::chase on near_p1, which identifies the predators near p1, even if it was initially
    // intended
    // to be applied on near_boids

    double chase1_x = c * 2 * d / 3. * (1.3 * std::sin(alfa) + 0.8 * std::sin(beta));
    double chase1_y = c * 2 * -d / 3. * (1.3 * std::cos(alfa) + 0.8 * std::cos(beta));

    CHECK(p1.chase(c, near_p1).getX() == doctest::Approx(chase1_x));
    CHECK(p1.chase(c, near_p1).getY() == doctest::Approx(chase1_y));
  }

  SUBCASE("Testing friction method") {
    p1.friction(maxSpeed, v1);
    p2.friction(maxSpeed, v2);
    p3.friction(maxSpeed, v3);
    p4.friction(maxSpeed, v4);

    CHECK(v1.getX() == doctest::Approx(maxSpeed[1] * std::sin(vel1.angle())));
    CHECK(v1.getY() == doctest::Approx(-maxSpeed[1] * std::cos(vel1.angle())));

    CHECK(v2.getX() == doctest::Approx(maxSpeed[1] * std::sin(vel2.angle())));
    CHECK(v2.getY() == doctest::Approx(-maxSpeed[1] * std::cos(vel2.angle())));

    CHECK(v3.getX() == doctest::Approx(maxSpeed[1] * std::sin(vel3.angle())));
    CHECK(v3.getY() == doctest::Approx(-maxSpeed[1] * std::cos(vel3.angle())));

    CHECK(v4 == Point(-1., -2.));
  }

  SUBCASE("Testing boost method") {
    p1.boost(minSpeed, v1);
    p2.boost(minSpeed, v2);
    p3.boost(minSpeed, v3);
    p4.boost(minSpeed, v4);

    CHECK(v1 == Point(5., -1.));
    CHECK(v2 == Point(-8.5, -6.));
    CHECK(v3 == Point(-7.3, 2.5));

    CHECK(v4.getX() == doctest::Approx(minSpeed[1] * std::sin(vel4.angle())));
    CHECK(v4.getY() == doctest::Approx(-minSpeed[1] * std::cos(vel4.angle())));
  }
}

//======================================================================================================================
//===TESTING FUNCTIONS IN NAMESPACE TRIANGLES::=========================================================================
//======================================================================================================================

Flock flock1(2, 2);

std::shared_ptr<Boid> b1 = std::make_shared<Boid>(pos1, vel1);
std::shared_ptr<Boid> b2 = std::make_shared<Boid>(pos2, vel2);
std::shared_ptr<Predator> p1 = std::make_shared<Predator>(pos3, vel3);
std::shared_ptr<Predator> p2 = std::make_shared<Predator>(pos5, vel5);
// Boid b1(pos1, vel1);
std::vector<std::shared_ptr<Bird>> f1{};

TEST_CASE("Testing functions in namespace triangles::") {
  f1.push_back(b1);
  f1.push_back(b2);
  f1.push_back(p1);
  f1.push_back(p2);
  f1.resize(4);

  CHECK(flock1.getFlockSize() == f1.size());
  flock1.setFlock(f1);

  sf::Vertex v1{pos1()};
  sf::Vertex v2{pos3()};

  float height{triangles::getHeight()};
  float base_width{triangles::getBaseWidth()};

  sf::VertexArray triangles(sf::Triangles, 3 * flock1.getFlockSize());

  SUBCASE("Testing triangles::createTriangles()") {
    triangles::createTriangles(flock1, triangles);

    CHECK(triangles[0].color == sf::Color::Blue);
    CHECK(triangles[1].color == sf::Color::Blue);
    CHECK(triangles[2].color == sf::Color::Blue);

    CHECK(triangles[0].position == v1.position + sf::Vector2f(0, -height / 2));
    CHECK(triangles[1].position == v1.position + sf::Vector2f(-base_width / 2, height / 2));
    CHECK(triangles[2].position == v1.position + sf::Vector2f(base_width / 2, height / 2));

    CHECK(triangles[6].color == sf::Color::Red);
    CHECK(triangles[7].color == sf::Color::Red);
    CHECK(triangles[8].color == sf::Color::Red);

    CHECK(triangles[6].position == v2.position + sf::Vector2f(0, -(height * 3 / 2) / 2));
    CHECK(triangles[7].position == v2.position + sf::Vector2f(-(base_width * 3 / 2) / 2, (height * 3 / 2) / 2));
    CHECK(triangles[8].position == v2.position + sf::Vector2f((base_width * 3 / 2) / 2, (height * 3 / 2) / 2));

    CHECK(static_cast<int>(triangles.getVertexCount()) == 4 * 3);
  }
  SUBCASE("Testing triangles::rotateTriangles()") {
    double theta1{2.5};
    double theta2{3.6};

    triangles::rotateTriangle(b1, triangles, theta1, 0);
    triangles::rotateTriangle(p1, triangles, theta2, 2);

    CHECK(triangles[0].position ==
           v1.position + sf::Vector2f(static_cast<float>(triangles::relative_position[0].x * std::cos(theta1) -
                                                         triangles::relative_position[0].y * std::sin(theta1)),
                                      static_cast<float>(triangles::relative_position[0].x * std::sin(theta1) +
                                                         triangles::relative_position[0].y * std::cos(theta1))));
    CHECK(triangles[1].position ==
           v1.position + sf::Vector2f(static_cast<float>(triangles::relative_position[1].x * std::cos(theta1) -
                                                         triangles::relative_position[1].y * std::sin(theta1)),
                                      static_cast<float>(triangles::relative_position[1].x * std::sin(theta1) +
                                                         triangles::relative_position[1].y * std::cos(theta1))));

    CHECK(triangles[2].position ==
           v1.position + sf::Vector2f(static_cast<float>(triangles::relative_position[2].x * std::cos(theta1) -
                                                         triangles::relative_position[2].y * std::sin(theta1)),
                                      static_cast<float>(triangles::relative_position[2].x * std::sin(theta1) +
                                                         triangles::relative_position[2].y * std::cos(theta1))));

    CHECK(triangles[6].position ==
           v2.position + sf::Vector2f(static_cast<float>(triangles::relative_position[3].x * std::cos(theta2) -
                                                         triangles::relative_position[3].y * std::sin(theta2)),
                                      static_cast<float>(triangles::relative_position[3].x * std::sin(theta2) +
                                                         triangles::relative_position[3].y * std::cos(theta2))));

    CHECK(triangles[7].position ==
           v2.position + sf::Vector2f(static_cast<float>(triangles::relative_position[4].x * std::cos(theta2) -
                                                         triangles::relative_position[4].y * std::sin(theta2)),
                                      static_cast<float>(triangles::relative_position[4].x * std::sin(theta2) +
                                                         triangles::relative_position[4].y * std::cos(theta2))));
    CHECK(triangles[8].position ==
           v2.position + sf::Vector2f(static_cast<float>(triangles::relative_position[5].x * std::cos(theta2) -
                                                         triangles::relative_position[5].y * std::sin(theta2)),
                                      static_cast<float>(triangles::relative_position[5].x * std::sin(theta2) +
                                                         triangles::relative_position[5].y * std::cos(theta2))));
  }
}

//======================================================================================================================
//===TESTING FLOCK CLASS================================================================================================
//======================================================================================================================

TEST_CASE("Testing Flock class") {
  sf::VertexArray triangles(sf::Triangles, 3 * flock1.getFlockSize());

  SUBCASE("Testing generateBirds method") {
    Flock flock0(2, 2);
    flock0.generateBirds();
    CHECK(!flock0.getFlock().empty());
  }

  SUBCASE("Testing getters and setters") {
    CHECK(flock1.getFlockSize() == doctest::Approx(4));
    CHECK(flock1.getBoidsNum() == doctest::Approx(2));
    CHECK(flock1.getPredatorsNum() == doctest::Approx(2));
  }

  SUBCASE("Testing findNearBoids method") {
    std::vector<std::shared_ptr<Bird>> nearBoids1;
    nearBoids1 = flock1.findNearBoids(*b1, 0);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearBoids1[0].get() == b2.get());

    std::vector<std::shared_ptr<Bird>> nearBoids2;
    nearBoids2 = flock1.findNearBoids(*p1, 2);

    CHECK(nearBoids2.size() == 2);
    CHECK(nearBoids2[0] == b1);
    CHECK(nearBoids2[1] == b2);
  }

  SUBCASE("Testing findNearPredators method") {
    std::vector<std::shared_ptr<Bird>> nearPredators1;
    nearPredators1 = flock1.findNearPredators(*b1, 0);

    CHECK(nearPredators1.size() == 2);
    CHECK(nearPredators1[0] == p1);
    CHECK(nearPredators1[1] == p2);

    std::vector<std::shared_ptr<Bird>> nearPredators2;
    nearPredators2 = flock1.findNearPredators(*p1, 2);

    CHECK(nearPredators2.size() == 1);
    CHECK(nearPredators2[0] == p2);

    Flock flock2(2, 0);
    std::vector<std::shared_ptr<Bird>> f2;
    f2.push_back(b1);
    f2.push_back(b2);

    CHECK(flock2.findNearPredators(*b1, 0).empty());
  }

  flock1.setMaxSpeed(5., 4.);
  flock1.setMinSpeed(3, 2.5);
  std::array<Point, 2> update_boid = flock1.updateBird(b1, triangles, 0);
  std::array<Point, 2> update_predator = flock1.updateBird(p1, triangles, 2);

  SUBCASE("Testing updateBird method") {
    const std::array<double, 2> border_params = flock1.getBorderParams();

    CHECK(border_params[0] > 0);
    CHECK(border_params[1] > 0);
    CHECK(border_params[0] < graphic_par::statsWidth);
    CHECK(border_params[0] <= graphic_par::windowHeight);

    std::vector<std::shared_ptr<Bird>> nearBoids1;
    std::vector<std::shared_ptr<Bird>> nearPredators1;
    nearBoids1 = flock1.findNearBoids(*b1, 0);
    nearPredators1 = flock1.findNearPredators(*b1, 0);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearPredators1.size() == 2);

    Point v_boid = vel1 + b1->border(border_params[0], border_params[1], v_boid) + b1->separation(s, ds, nearBoids1) +
                   b1->alignment(a, nearBoids1) + b1->cohesion(c, nearBoids1) + b1->repel(s, nearPredators1);
    b1->friction(maxSpeed, v_boid);
    b1->boost(minSpeed, v_boid);
    Point p_boid = pos1 + graphic_par::dt * v_boid;

    CHECK(update_boid[0].getX() == doctest::Approx(p_boid.getX()));
    CHECK(update_boid[0].getY() == doctest::Approx(p_boid.getY()));
    CHECK(update_boid[1].getX() == doctest::Approx(v_boid.getX()));
    CHECK(update_boid[1].getY() == doctest::Approx(v_boid.getY()));

    std::vector<std::shared_ptr<Bird>> nearBoids2;
    std::vector<std::shared_ptr<Bird>> nearPredators2;
    nearBoids2 = flock1.findNearBoids(*p1, 2);
    nearPredators2 = flock1.findNearPredators(*p1, 2);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearPredators1.size() == 2);

    Point v_predator = vel3 + p1->border(border_params[0], border_params[1], v_predator) +
                       p1->separation(s * 0.1, d * 0.5, nearPredators2) + p1->chase(c, nearBoids2);

    p1->friction(maxSpeed, v_predator);
    p1->boost(minSpeed, v_predator);
    Point p_predator = pos3 + graphic_par::dt * v_predator;

    CHECK(update_predator[0].getX() == doctest::Approx(p_predator.getX()));
    CHECK(update_predator[0].getY() == doctest::Approx(p_predator.getY()));
    CHECK(update_predator[1].getX() == doctest::Approx(v_predator.getX()));
    CHECK(update_predator[1].getY() == doctest::Approx(v_predator.getY()));
  }

  SUBCASE("Testing evolve method") {
    flock1.evolve(triangles);
    triangles::createTriangles(flock1, triangles);

    Boid boid(update_boid[0], update_boid[1]);
    Boid predator(update_predator[0], update_predator[1]);

    CHECK(flock1.getFlock()[0]->getPosition().getX() == boid.getPosition().getX());
    CHECK(flock1.getFlock()[0]->getPosition().getY() == boid.getPosition().getY());
    CHECK(flock1.getFlock()[0]->getVelocity().getX() == boid.getVelocity().getX());
    CHECK(flock1.getFlock()[0]->getVelocity().getY() == boid.getVelocity().getY());

    CHECK(triangles[0].color == sf::Color::Blue);
    CHECK(triangles[1].color == sf::Color::Blue);
    CHECK(triangles[2].color == sf::Color::Blue);

    CHECK(flock1.getFlock()[2]->getPosition().getX() == predator.getPosition().getX());
    CHECK(flock1.getFlock()[2]->getPosition().getY() == predator.getPosition().getY());
    CHECK(flock1.getFlock()[2]->getVelocity().getX() == predator.getVelocity().getX());
    CHECK(flock1.getFlock()[2]->getVelocity().getY() == predator.getVelocity().getY());

    CHECK(triangles[6].color == sf::Color::Red);
    CHECK(triangles[7].color == sf::Color::Red);
    CHECK(triangles[8].color == sf::Color::Red);
  }

  SUBCASE("Testing statistics method") {
    Statistics stats = flock1.statistics();

    double speed1 = flock1.getFlock()[0]->getVelocity().module();
    double speed2 = flock1.getFlock()[1]->getVelocity().module();

    double mean_speed = (speed1 + speed2) / 2.;
    double mean_speed2 = (speed1 * speed1 + speed2 * speed2) / 2.;

    CHECK(stats.mean_dist ==
           doctest::Approx(flock1.getFlock()[0]->getPosition().distance(flock1.getFlock()[1]->getPosition())));
    CHECK(stats.mean_speed == doctest::Approx(mean_speed));
    CHECK(stats.dev_dist == doctest::Approx(0.));
    CHECK(stats.dev_speed == doctest::Approx(std::sqrt(mean_speed2 - mean_speed * mean_speed)));

    CHECK(flock1.getBoidsNum() > 1);
  }
}

//======================================================================================================================
//===TESTING STATISTICS STRUCT==========================================================================================
//======================================================================================================================

TEST_CASE("Testing Statistics struct") {
  SUBCASE("Testing default and parametric constructors") {
    Statistics stats0;
    Statistics stats1(7., 3., 2., 0.5);

    CHECK(stats0.mean_dist == 0.);
    CHECK(stats0.dev_dist == 0.);
    CHECK(stats0.mean_speed == 0.);
    CHECK(stats0.dev_speed == 0.);

    CHECK(stats1.mean_dist == 7.);
    CHECK(stats1.dev_dist == 3.);
    CHECK(stats1.mean_speed == 2.);
    CHECK(stats1.dev_speed == 0.5);
  }
}