#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <vector>

#include "../doctest.h"
#include "../include/bird.hpp"
#include "../include/flock.hpp"
#include "../include/graphic.hpp"
#include "../include/point.hpp"
#include "../include/triangle.hpp"

constexpr double d{80.};
constexpr double ds{d / 2.};
constexpr double s{0.6};
constexpr double c{0.001};
constexpr double a{0.6};

constexpr std::array<double, 2> maxSpeed{5., 4.};
constexpr std::array<double, 2> minSpeed{3., 2.5};

//======================================================================================================================
//===TESTING POINT CLASS================================================================================================
//======================================================================================================================

TEST_CASE("Testing Point class") {
  point::Point p0;
  point::Point p1(1., 1.);
  point::Point p2(-5.2, 3.75);
  point::Point p3(-2., -4.);
  point::Point p4(1., -6.);

  double scalar1 = 7.;
  double scalar2 = -11.;

  SUBCASE("Testing getters") {
    CHECK(p0 == point::Point(0., 0.));
    CHECK(p1 == point::Point(1., 1.));
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
    point::Point sum1 = p0 + p1;
    point::Point sum2 = p1 + p0;

    point::Point sum3 = p1 + p2;
    point::Point sum4 = p2 + p1;

    CHECK(sum1 == point::Point(1., 1.));
    CHECK(sum2 == point::Point(1., 1.));
    CHECK(sum3 == point::Point(-4.2, 4.75));
    CHECK(sum4 == point::Point(-4.2, 4.75));
  }

  SUBCASE("Testing operator -") {
    point::Point diff1 = p0 - p1;
    point::Point diff2 = p1 - p0;

    point::Point diff3 = p1 - p2;
    point::Point diff4 = p2 - p1;

    point::Point diff5 = p2 - p0;
    point::Point diff6 = p0 - p2;

    CHECK(diff1 == point::Point(-1., -1));
    CHECK(diff2 == point::Point(1., 1.));
    CHECK(diff3 == point::Point(6.2, -2.75));
    CHECK(diff4 == point::Point(-6.2, 2.75));
    CHECK(diff5 == point::Point(-5.2, 3.75));
    CHECK(diff6 == point::Point(5.2, -3.75));
  }

  SUBCASE("Testing operator *") {
    double scalar0 = 0.;
    point::Point prod1 = scalar0 * p0;
    point::Point prod2 = scalar0 * p1;
    point::Point prod3 = scalar0 * p2;

    point::Point prod4 = scalar1 * p0;
    point::Point prod5 = scalar1 * p1;
    point::Point prod6 = scalar1 * p2;

    point::Point prod7 = scalar2 * p0;
    point::Point prod8 = scalar2 * p1;
    point::Point prod9 = scalar2 * p2;

    CHECK(prod1 == point::Point(0., 0.));
    CHECK(prod2 == point::Point(0., 0.));
    CHECK(prod3 == point::Point(0., 0.));
    CHECK(prod4 == point::Point(0., 0.));
    CHECK(prod5 == point::Point(7., 7.));
    CHECK(prod6 == point::Point(-36.4, 26.25));
    CHECK(prod7 == point::Point(0., 0.));
    CHECK(prod8 == point::Point(-11., -11.));
    CHECK(prod9 == point::Point(57.2, -41.25));
  }

  SUBCASE("Testing operator /") {
    point::Point div2 = p1 / scalar1;
    point::Point div3 = p1 / scalar2;
    point::Point div4 = p0 / scalar1;
    point::Point div5 = p2 / scalar1;
    point::Point div6 = p2 / scalar2;

    CHECK(div2.getX() == doctest::Approx(0.142857));
    CHECK(div2.getY() == doctest::Approx(0.142857));

    CHECK(div3.getX() == doctest::Approx(-0.090909090));
    CHECK(div3.getY() == doctest::Approx(-0.090909090));

    CHECK(div4 == point::Point(0., 0.));

    CHECK(div5.getX() == doctest::Approx(-0.742857));
    CHECK(div5.getY() == doctest::Approx(0.535714));

    CHECK(div6.getX() == doctest::Approx(0.472727));
    CHECK(div6.getY() == doctest::Approx(-0.340909090));
  }
  SUBCASE("Testing operator +=") {
    point::Point start0 = p0;
    point::Point start1(8., -6.);

    start0 += p1;
    start1 += p2;

    CHECK(start0 == point::Point(1., 1.));
    CHECK(start1 == point::Point(2.8, -2.25));
  }
  SUBCASE("Testing operator ==") {
    point::Point point0 = p0;
    point::Point point1 = p1;
    point::Point point2 = p2;

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

point::Point pos1(3., -2.);
point::Point vel1(5., -1.);
double alfa{M_PI / 3. + vel1.angle()};
double beta{-1 * M_PI / 3. + vel1.angle()};

point::Point pos2 = pos1 + 0.8 * d * point::Point(std::sin(alfa), -std::cos(alfa));
point::Point vel2(-8.5, -6.);

point::Point pos3 = pos1 + 0.8 * d * point::Point(std::sin(beta), -std::cos(beta));
point::Point vel3(-7.3, 2.5);

point::Point pos4 = pos1 + 0.5 * ds * point::Point(std::sin(alfa), -std::cos(alfa));
point::Point vel4(-1., -2.);

point::Point pos5 = pos1 + 0.5 * ds * point::Point(std::sin(beta), -std::cos(beta));
point::Point vel5(-5., -3.2);

TEST_CASE("Testing Boid class") {
  double x = pos1.getX();
  double y = pos1.getY();

  bird::Boid b1(pos1, vel1);
  bird::Boid b2(pos2, vel2);
  bird::Boid b3(pos3, vel3);
  bird::Boid b4(pos4, vel4);
  bird::Boid b5;

  b5.setBird(pos5, vel5);

  point::Point v1 = vel1;
  point::Point v2 = vel2;
  point::Point v3 = vel3;
  point::Point v4 = vel4;
  point::Point v5 = vel5;

  std::vector<std::shared_ptr<bird::Bird>> near_b1{std::make_shared<bird::Boid>(b2), std::make_shared<bird::Boid>(b3),
                                                   std::make_shared<bird::Boid>(b4), std::make_shared<bird::Boid>(b5)};

  SUBCASE("Testing getters") {
    bird::Boid b0;
    CHECK(b0.getPosition() == point::Point(0., 0.));
    CHECK(b0.getVelocity() == point::Point(0., 0.));

    CHECK(b1.getPosition() == point::Point(3., -2.));
    CHECK(b1.getVelocity() == point::Point(5., -1.));
  }

  SUBCASE("Testing setters") {
    CHECK(b5.getPosition().getX() == doctest::Approx(pos5.getX()));
    CHECK(b5.getPosition().getY() == doctest::Approx(pos5.getY()));

    CHECK(b5.getVelocity() == point::Point(-5., -3.2));
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
    // here we apply bird::Boid::repel on near_b1, which identifies the boids near b1, even if it was initially intended
    // to be applied on near_predators.

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

    CHECK(v1 == point::Point(5., -1.));
    CHECK(v2 == point::Point(-8.5, -6.));
    CHECK(v3 == point::Point(-7.3, 2.5));

    CHECK(v4.getX() == doctest::Approx(minSpeed[0] * std::sin(vel4.angle())));
    CHECK(v4.getY() == doctest::Approx(-minSpeed[0] * std::cos(vel4.angle())));

    CHECK(v5 == point::Point(-5., -3.2));
  }

  SUBCASE("Testing border method") {
    constexpr double margin{100.};
    constexpr double turn_factor{1.5};

    bird::Boid boid0;
    bird::Boid boid1(point::Point(graphic_par::stats_width + margin + 2., margin / 2.), vel1);
    bird::Boid boid2(point::Point(graphic_par::stats_width + margin + 2., graphic_par::window_height - margin / 2.),
                     vel2);
    bird::Boid boid3(point::Point(graphic_par::stats_width + margin / 2., margin + 5.), vel3);
    bird::Boid boid4(point::Point(graphic_par::window_width - margin / 2., margin + 5.), vel4);
    bird::Boid boid5(point::Point(graphic_par::window_width / 2., graphic_par::window_height / 2.), vel5);

    point::Point velocity0;
    point::Point velocity1;
    point::Point velocity2;
    point::Point velocity3;
    point::Point velocity4;
    point::Point velocity5;

    velocity0 += boid0.border(margin, turn_factor);
    velocity1 += boid1.border(margin, turn_factor);
    velocity2 += boid2.border(margin, turn_factor);
    velocity3 += boid3.border(margin, turn_factor);
    velocity4 += boid4.border(margin, turn_factor);
    velocity5 += boid5.border(margin, turn_factor);

    CHECK(velocity0.getX() == doctest::Approx(turn_factor));
    CHECK(velocity0.getY() == doctest::Approx(turn_factor));

    CHECK(velocity1.getX() == doctest::Approx(vel1.getX()));
    CHECK(velocity1.getY() == doctest::Approx(vel1.getY() + turn_factor));

    CHECK(velocity2.getX() == doctest::Approx(vel2.getX()));
    CHECK(velocity2.getY() == doctest::Approx(vel2.getY() - turn_factor));

    CHECK(velocity3.getX() == doctest::Approx(vel3.getX() + turn_factor));
    CHECK(velocity3.getY() == doctest::Approx(vel3.getY()));

    CHECK(velocity4.getX() == doctest::Approx(vel4.getX() - turn_factor));
    CHECK(velocity4.getY() == doctest::Approx(vel4.getY()));

    CHECK(velocity5.getX() == doctest::Approx(vel5.getX()));
    CHECK(velocity5.getY() == doctest::Approx(vel5.getY()));
  }
};

//======================================================================================================================
//===TESTING PREDATOR CLASS=============================================================================================
//======================================================================================================================

TEST_CASE("Testing Predator class") {
  bird::Predator p1(pos1, vel1);
  bird::Predator p2(pos2, vel2);
  bird::Predator p3(pos3, vel3);
  bird::Predator p4;

  pos4 = pos1 + 0.5 * d * point::Point(std::sin(alfa), -std::cos(alfa));
  p4.setBird(pos4, vel4);

  point::Point v1 = vel1;
  point::Point v2 = vel2;
  point::Point v3 = vel3;
  point::Point v4 = vel4;

  std::vector<std::shared_ptr<bird::Bird>> near_p1{
      std::make_shared<bird::Predator>(p2), std::make_shared<bird::Predator>(p3), std::make_shared<bird::Predator>(p4)};

  SUBCASE("Testing getters") {
    bird::Predator p0;
    CHECK(p0.getPosition() == point::Point(0., 0.));
    CHECK(p0.getVelocity() == point::Point(0., 0.));
    CHECK(p1.getPosition() == point::Point(3., -2.));
    CHECK(p1.getVelocity() == point::Point(5., -1.));
  }

  SUBCASE("Testing setters") {
    CHECK(p2.getPosition().getX() == doctest::Approx(pos2.getX()));
    CHECK(p2.getPosition().getY() == doctest::Approx(pos2.getY()));
    CHECK(p2.getVelocity() == point::Point(-8.5, -6.));

    CHECK(p3.getPosition().getX() == doctest::Approx(pos3.getX()));
    CHECK(p3.getPosition().getY() == doctest::Approx(pos3.getY()));
    CHECK(p3.getVelocity() == point::Point(-7.3, 2.5));

    CHECK(p4.getPosition().getX() == doctest::Approx(pos4.getX()));
    CHECK(p4.getPosition().getY() == doctest::Approx(pos4.getY()));
    CHECK(p4.getVelocity() == point::Point(-1., -2.));
  }

  SUBCASE("Testing chase method") {
    // here we apply bird::Predator::chase on near_p1, which identifies the predators near p1, even if it was initially
    // intended to be applied on near_boids.

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

    CHECK(v4 == point::Point(-1., -2.));
  }

  SUBCASE("Testing boost method") {
    p1.boost(minSpeed, v1);
    p2.boost(minSpeed, v2);
    p3.boost(minSpeed, v3);
    p4.boost(minSpeed, v4);

    CHECK(v1 == point::Point(5., -1.));
    CHECK(v2 == point::Point(-8.5, -6.));
    CHECK(v3 == point::Point(-7.3, 2.5));

    CHECK(v4.getX() == doctest::Approx(minSpeed[1] * std::sin(vel4.angle())));
    CHECK(v4.getY() == doctest::Approx(-minSpeed[1] * std::cos(vel4.angle())));
  }
}

//======================================================================================================================
//===TESTING FUNCTIONS IN NAMESPACE GRAPHIC_PAR=========================================================================
//======================================================================================================================
TEST_CASE("Testing functions in namespace graphic_par") {
  SUBCASE("Testing graphic_par::getPositiveInteger()") {
    std::istringstream input1("5\n");
    std::istringstream input2("0\n");
    std::istringstream input3("-1\n");

    std::ostringstream output1;
    std::ostringstream output2;
    std::ostringstream output3;

    CHECK(graphic_par::getPositiveInteger("Enter a positive integer, might be zero: ", input1, output1, false) ==
          doctest::Approx(5));
    CHECK(graphic_par::getPositiveInteger("Enter a positive integer: ", input2, output2, true) == doctest::Approx(0));
    CHECK_THROWS_AS(graphic_par::getPositiveInteger("Enter a positive integer: ", input3, output3, true),
                    std::exception);

    CHECK(output1.str() == "Enter a positive integer, might be zero: ");
    CHECK(output2.str() == "Enter a positive integer: ");
    CHECK(output3.str() == "Enter a positive integer: \nInvalid input. The program will now terminate.\n");
  }

  SUBCASE("Testing graphic_par::getPositiveDouble()") {
    std::istringstream input1("5.5\n");
    std::istringstream input2("1.\n");
    std::istringstream input3("0.\n");
    std::istringstream input4("-1.\n");

    std::ostringstream output1;
    std::ostringstream output2;
    std::ostringstream output3;
    std::ostringstream output4;

    CHECK(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input1, output1) == doctest::Approx(5.5));
    CHECK(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input2, output2) == doctest::Approx(1.));
    CHECK(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input3, output3) == doctest::Approx(0.));
    CHECK_THROWS_AS(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input4, output4),
                    std::exception);

    CHECK(output1.str() == "Enter a double between 0 and 1: ");
    CHECK(output2.str() == "Enter a double between 0 and 1: ");
    CHECK(output3.str() == "Enter a double between 0 and 1: ");
    CHECK(output4.str() == "Enter a double between 0 and 1: \nInvalid input. The program will now terminate.\n");
  }

  SUBCASE("Testing graphic_par::createRectangle()") {}
}
//======================================================================================================================
//===TESTING FUNCTIONS IN NAMESPACE TRIANGLES::=========================================================================
//======================================================================================================================

flock::Flock flock1(2, 2, maxSpeed, minSpeed);

std::shared_ptr<bird::Boid> b1 = std::make_shared<bird::Boid>(pos1, vel1);
std::shared_ptr<bird::Boid> b2 = std::make_shared<bird::Boid>(pos2, vel2);
std::shared_ptr<bird::Predator> p1 = std::make_shared<bird::Predator>(pos3, vel3);
std::shared_ptr<bird::Predator> p2 = std::make_shared<bird::Predator>(pos5, vel5);

std::vector<std::shared_ptr<bird::Bird>> f1{};

TEST_CASE("Testing functions in namespace triangles") {
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

    CHECK(triangles[0].color == sf::Color::Black);
    CHECK(triangles[1].color == sf::Color::Black);
    CHECK(triangles[2].color == sf::Color::Black);

    CHECK(triangles[0].position == v1.position + sf::Vector2f(0, -height / 2));
    CHECK(triangles[1].position == v1.position + sf::Vector2f(-base_width / 2, height / 2));
    CHECK(triangles[2].position == v1.position + sf::Vector2f(base_width / 2, height / 2));

    CHECK(triangles[6].color == sf::Color(128, 0, 32));
    CHECK(triangles[7].color == sf::Color(128, 0, 32));
    CHECK(triangles[8].color == sf::Color(128, 0, 32));

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
    flock::Flock flock0(2, 2);
    flock0.generateBirds();
    CHECK(!flock0.getFlock().empty());
  }

  SUBCASE("Testing getters and setters") {
    CHECK(flock1.getFlockSize() == doctest::Approx(4));
    CHECK(flock1.getBoidsNum() == doctest::Approx(2));
    CHECK(flock1.getPredatorsNum() == doctest::Approx(2));
  }

  SUBCASE("Testing findNearBoids method") {
    std::vector<std::shared_ptr<bird::Bird>> nearBoids1;
    nearBoids1 = flock1.findNearBoids(*b1, 0);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearBoids1[0].get() == b2.get());

    std::vector<std::shared_ptr<bird::Bird>> nearBoids2;
    nearBoids2 = flock1.findNearBoids(*p1, 2);

    CHECK(nearBoids2.size() == 2);
    CHECK(nearBoids2[0] == b1);
    CHECK(nearBoids2[1] == b2);
  }

  SUBCASE("Testing findNearPredators method") {
    std::vector<std::shared_ptr<bird::Bird>> nearPredators1;
    nearPredators1 = flock1.findNearPredators(*b1, 0);

    CHECK(nearPredators1.size() == 2);
    CHECK(nearPredators1[0] == p1);
    CHECK(nearPredators1[1] == p2);

    std::vector<std::shared_ptr<bird::Bird>> nearPredators2;
    nearPredators2 = flock1.findNearPredators(*p1, 2);

    CHECK(nearPredators2.size() == 1);
    CHECK(nearPredators2[0] == p2);

    flock::Flock flock2(2, 0);
    std::vector<std::shared_ptr<bird::Bird>> f2;
    f2.push_back(b1);
    f2.push_back(b2);

    CHECK(flock2.findNearPredators(*b1, 0).empty());
  }

  std::array<point::Point, 2> update_boid = flock1.updateBird(b1, triangles, 0);
  std::array<point::Point, 2> update_predator = flock1.updateBird(p1, triangles, 2);

  SUBCASE("Testing updateBird method") {
    const std::array<double, 2> border_params = flock1.getBorderParams();

    CHECK(border_params[0] > 0);
    CHECK(border_params[1] > 0);
    CHECK(border_params[0] < graphic_par::stats_width);
    CHECK(border_params[0] <= graphic_par::window_height);

    std::vector<std::shared_ptr<bird::Bird>> nearBoids1;
    std::vector<std::shared_ptr<bird::Bird>> nearPredators1;
    nearBoids1 = flock1.findNearBoids(*b1, 0);
    nearPredators1 = flock1.findNearPredators(*b1, 0);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearPredators1.size() == 2);

    point::Point v_boid = b1->border(border_params[0], border_params[1]) + b1->separation(s, ds, nearBoids1) +
                          b1->alignment(a, nearBoids1) + b1->cohesion(c, nearBoids1) + b1->repel(s, nearPredators1);
    b1->friction(maxSpeed, v_boid);
    b1->boost(minSpeed, v_boid);
    point::Point p_boid = b1->getPosition() + graphic_par::dt * v_boid;

    CHECK(update_boid[0].getX() == doctest::Approx(p_boid.getX()));
    CHECK(update_boid[0].getY() == doctest::Approx(p_boid.getY()));
    CHECK(update_boid[1].getX() == doctest::Approx(v_boid.getX()));
    CHECK(update_boid[1].getY() == doctest::Approx(v_boid.getY()));

    std::vector<std::shared_ptr<bird::Bird>> nearBoids2;
    std::vector<std::shared_ptr<bird::Bird>> nearPredators2;
    nearBoids2 = flock1.findNearBoids(*p1, 2);
    nearPredators2 = flock1.findNearPredators(*p1, 2);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearPredators1.size() == 2);

    point::Point v_predator = p1->border(border_params[0], border_params[1]) +
                              p1->separation(s * 0.1, d * 0.5, nearPredators2) + p1->chase(c, nearBoids2);

    p1->friction(maxSpeed, v_predator);
    p1->boost(minSpeed, v_predator);
    point::Point p_predator = p1->getPosition() + graphic_par::dt * v_predator;

    CHECK(update_predator[0].getX() == doctest::Approx(p_predator.getX()));
    CHECK(update_predator[0].getY() == doctest::Approx(p_predator.getY()));
    CHECK(update_predator[1].getX() == doctest::Approx(v_predator.getX()));
    CHECK(update_predator[1].getY() == doctest::Approx(v_predator.getY()));
  }

  SUBCASE("Testing evolve method") {
    flock1.evolve(triangles);
    triangles::createTriangles(flock1, triangles);

    bird::Boid boid(update_boid[0], update_boid[1]);
    bird::Predator predator(update_predator[0], update_predator[1]);

    CHECK(flock1.getFlock()[0]->getPosition().getX() == boid.getPosition().getX());
    CHECK(flock1.getFlock()[0]->getPosition().getY() == boid.getPosition().getY());
    CHECK(flock1.getFlock()[0]->getVelocity().getX() == boid.getVelocity().getX());
    CHECK(flock1.getFlock()[0]->getVelocity().getY() == boid.getVelocity().getY());

    CHECK(triangles[0].color == sf::Color::Black);
    CHECK(triangles[1].color == sf::Color::Black);
    CHECK(triangles[2].color == sf::Color::Black);

    CHECK(flock1.getFlock()[2]->getPosition().getX() == predator.getPosition().getX());
    CHECK(flock1.getFlock()[2]->getPosition().getY() == predator.getPosition().getY());
    CHECK(flock1.getFlock()[2]->getVelocity().getX() == predator.getVelocity().getX());
    CHECK(flock1.getFlock()[2]->getVelocity().getY() == predator.getVelocity().getY());

    CHECK(triangles[6].color == sf::Color(128, 0, 32));
    CHECK(triangles[7].color == sf::Color(128, 0, 32));
    CHECK(triangles[8].color == sf::Color(128, 0, 32));
  }

  SUBCASE("Testing statistics method") {
    statistics::Statistics stats = flock1.statistics();

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
    statistics::Statistics stats0;
    statistics::Statistics stats1(7., 3., 2., 0.5);

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

// TODO: decidere se vogliamo testare funzione flock::setFlockParams()
// TODO: testare graphic_par::createRectangle()