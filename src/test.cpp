#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <vector>

#include "../doctest.h"
#include "../include/bird.hpp"
#include "../include/flock.hpp"
#include "../include/graphic.hpp"
#include "../include/point.hpp"
#include "../include/triangle.hpp"

std::array<double, 3> distanceParams = flock::Flock::getDistancesParams();

double d{distanceParams[0]};
double b_ds{distanceParams[1]};
double p_ds{distanceParams[2]};

constexpr double bMaxSpeed{5.};
constexpr double pMaxSpeed{4.};

constexpr double bMinSpeed{3.};
constexpr double pMinSpeed{2.5};

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

const point::Point pos1(3., -2.);
const point::Point vel1(5., -1.);
const double alfa{M_PI / 3. + vel1.angle()};
const double beta{-1 * M_PI / 3. + vel1.angle()};

const point::Point pos2 = pos1 + 0.8 * d * point::Point(std::sin(alfa), -std::cos(alfa));
const point::Point vel2(-8.5, -6.);

const point::Point pos3 = pos1 + 0.8 * d * point::Point(std::sin(beta), -std::cos(beta));
const point::Point vel3(-7.3, 2.5);

const point::Point pos4 = pos1 + 0.5 * b_ds * point::Point(std::sin(alfa), -std::cos(alfa));
const point::Point vel4(-1., -2.);

const point::Point pos5 = pos1 + 0.5 * b_ds * point::Point(std::sin(beta), -std::cos(beta));
const point::Point vel5(-5., -3.2);

TEST_CASE("Testing Boid class") {
  double s{0.1};
  double a{0.1};
  double c{0.004};
  double r{s * 6};

  const double x = pos1.getX();
  const double y = pos1.getY();

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
    double sep1_x = -s * 0.5 * b_ds * (std::sin(alfa) + std::sin(beta));
    double sep1_y = -s * 0.5 * b_ds * -(std::cos(alfa) + std::cos(beta));

    CHECK(b1.separation(s, b_ds, near_b1).getX() == doctest::Approx(sep1_x));
    CHECK(b1.separation(s, b_ds, near_b1).getY() == doctest::Approx(sep1_y));
  }

  SUBCASE("Testing cohesion method") {
    double coh1_x = c * ((4 * x + (0.5 * b_ds + 0.8 * d) * (std::sin(alfa) + std::sin(beta))) / 4. - x);
    double coh1_y = c * ((4 * y + (0.5 * b_ds + 0.8 * d) * -(std::cos(alfa) + std::cos(beta))) / 4. - y);

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

    double rep1_x = -r * (0.5 * b_ds + 0.8 * d) * (std::sin(alfa) + std::sin(beta));
    double rep1_y = -r * (0.5 * b_ds + 0.8 * d) * -(std::cos(alfa) + std::cos(beta));

    CHECK(b1.repel(r, near_b1).getX() == doctest::Approx(rep1_x));
    CHECK(b1.repel(r, near_b1).getY() == doctest::Approx(rep1_y));
  }

  SUBCASE("Testing friction method") {
    b1.friction(bMaxSpeed, v1);
    b2.friction(bMaxSpeed, v2);
    b3.friction(bMaxSpeed, v3);
    b4.friction(bMaxSpeed, v4);
    b5.friction(bMaxSpeed, v5);

    CHECK(v1.getX() == doctest::Approx(bMaxSpeed * std::sin(vel1.angle())));
    CHECK(v1.getY() == doctest::Approx(-bMaxSpeed * std::cos(vel1.angle())));

    CHECK(v2.getX() == doctest::Approx(bMaxSpeed * std::sin(vel2.angle())));
    CHECK(v2.getY() == doctest::Approx(-bMaxSpeed * std::cos(vel2.angle())));

    CHECK(v3.getX() == doctest::Approx(bMaxSpeed * std::sin(vel3.angle())));
    CHECK(v3.getY() == doctest::Approx(-bMaxSpeed * std::cos(vel3.angle())));

    CHECK(v4.getX() == doctest::Approx(vel4.getX()));
    CHECK(v4.getY() == doctest::Approx(vel4.getY()));

    CHECK(v5.getX() == doctest::Approx(bMaxSpeed * std::sin(vel5.angle())));
    CHECK(v5.getY() == doctest::Approx(-bMaxSpeed * std::cos(vel5.angle())));
  }

  SUBCASE("Testing boost method") {
    b1.boost(bMinSpeed, v1);
    b2.boost(bMinSpeed, v2);
    b3.boost(bMinSpeed, v3);
    b4.boost(bMinSpeed, v4);
    b5.boost(bMinSpeed, v5);

    CHECK(v1 == point::Point(5., -1.));
    CHECK(v2 == point::Point(-8.5, -6.));
    CHECK(v3 == point::Point(-7.3, 2.5));

    CHECK(v4.getX() == doctest::Approx(bMinSpeed * std::sin(vel4.angle())));
    CHECK(v4.getY() == doctest::Approx(-bMinSpeed * std::cos(vel4.angle())));

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
  double ch{0.004};

  bird::Predator p1(pos1, vel1);
  bird::Predator p2(pos2, vel2);
  bird::Predator p3(pos3, vel3);
  bird::Predator p4;

  const point::Point pos6 = pos1 + 0.5 * d * point::Point(std::sin(alfa), -std::cos(alfa));
  p4.setBird(pos6, vel4);

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

    CHECK(p4.getPosition().getX() == doctest::Approx(pos6.getX()));
    CHECK(p4.getPosition().getY() == doctest::Approx(pos6.getY()));
    CHECK(p4.getVelocity() == point::Point(-1., -2.));
  }

  SUBCASE("Testing chase method") {
    // here we apply bird::Predator::chase on near_p1, which identifies the predators near p1, even if it was initially
    // intended to be applied on near_boids.

    double chase1_x = ch * d / 3. * (1.3 * std::sin(alfa) + 0.8 * std::sin(beta));
    double chase1_y = ch * -d / 3. * (1.3 * std::cos(alfa) + 0.8 * std::cos(beta));

    CHECK(p1.chase(ch, near_p1).getX() == doctest::Approx(chase1_x));
    CHECK(p1.chase(ch, near_p1).getY() == doctest::Approx(chase1_y));
  }

  SUBCASE("Testing friction method") {
    p1.friction(pMaxSpeed, v1);
    p2.friction(pMaxSpeed, v2);
    p3.friction(pMaxSpeed, v3);
    p4.friction(pMaxSpeed, v4);

    CHECK(v1.getX() == doctest::Approx(pMaxSpeed * std::sin(vel1.angle())));
    CHECK(v1.getY() == doctest::Approx(-pMaxSpeed * std::cos(vel1.angle())));

    CHECK(v2.getX() == doctest::Approx(pMaxSpeed * std::sin(vel2.angle())));
    CHECK(v2.getY() == doctest::Approx(-pMaxSpeed * std::cos(vel2.angle())));

    CHECK(v3.getX() == doctest::Approx(pMaxSpeed * std::sin(vel3.angle())));
    CHECK(v3.getY() == doctest::Approx(-pMaxSpeed * std::cos(vel3.angle())));

    CHECK(v4 == point::Point(-1., -2.));
  }

  SUBCASE("Testing boost method") {
    p1.boost(pMinSpeed, v1);
    p2.boost(pMinSpeed, v2);
    p3.boost(pMinSpeed, v3);
    p4.boost(pMinSpeed, v4);

    CHECK(v1 == point::Point(5., -1.));
    CHECK(v2 == point::Point(-8.5, -6.));
    CHECK(v3 == point::Point(-7.3, 2.5));

    CHECK(v4.getX() == doctest::Approx(pMinSpeed * std::sin(vel4.angle())));
    CHECK(v4.getY() == doctest::Approx(-pMinSpeed * std::cos(vel4.angle())));
  }
}

//======================================================================================================================
//===TESTING FUNCTIONS IN NAMESPACE GRAPHIC_PAR=========================================================================
//======================================================================================================================
TEST_CASE("Testing functions in namespace graphic_par") {
  SUBCASE("Testing graphic_par::createRectangle()") {
    sf::VertexBuffer rectangle = graphic_par::createRectangle(graphic_par::stats_rectangle, 50, 50, 50);

    CHECK(rectangle.getPrimitiveType() == sf::TriangleStrip);
    CHECK(rectangle.getVertexCount() == graphic_par::stats_rectangle.size());
  }
  SUBCASE("Testing graphic_par::getPositiveInteger()") {
    std::istringstream input1("5\n");
    std::istringstream input2("0\n");
    std::istringstream input3("-1\n");

    std::ostringstream output1;
    std::ostringstream output2;
    std::ostringstream output3;

    CHECK(graphic_par::getPositiveInteger("Enter a positive integer, might be zero: ", input1, output1, false) == 5);

    CHECK_THROWS_WITH_AS(graphic_par::getPositiveInteger("Enter a positive integer: ", input2, output2, true),
                         "Error: Invalid input. The program will now terminate.", std::domain_error);
    CHECK_THROWS_WITH_AS(graphic_par::getPositiveInteger("Enter a positive integer: ", input3, output3, true),
                         "Error: Invalid input. The program will now terminate.", std::domain_error);

    CHECK(output1.str() == "Enter a positive integer, might be zero: ");
    CHECK(output2.str() == "Enter a positive integer: ");
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

    CHECK_THROWS_WITH_AS(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input1, output1),
                         "Error: Invalid input. The program will now terminate.", std::domain_error);
    CHECK(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input2, output2) == doctest::Approx(1.));
    CHECK(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input3, output3) == doctest::Approx(0.));
    CHECK_THROWS_WITH_AS(graphic_par::getPositiveDouble("Enter a double between 0 and 1: ", input4, output4),
                         "Error: Invalid input. The program will now terminate.", std::domain_error);

    CHECK(output1.str() == "Enter a double between 0 and 1: ");
    CHECK(output2.str() == "Enter a double between 0 and 1: ");
    CHECK(output3.str() == "Enter a double between 0 and 1: ");
  }
}
//======================================================================================================================
//===TESTING FUNCTIONS IN NAMESPACE TRIANGLES::=========================================================================
//======================================================================================================================

const std::shared_ptr<bird::Boid> b1 = std::make_shared<bird::Boid>(pos1, vel1);
const std::shared_ptr<bird::Boid> b2 = std::make_shared<bird::Boid>(pos2, vel2);
const std::vector<std::shared_ptr<bird::Boid>> boids{b1, b2};

const std::shared_ptr<bird::Predator> p1 = std::make_shared<bird::Predator>(pos3, vel3);
const std::shared_ptr<bird::Predator> p2 = std::make_shared<bird::Predator>(pos5, vel5);
const std::vector<std::shared_ptr<bird::Predator>> predators{p1, p2};

flock::Flock flock1(boids, predators, bMaxSpeed, pMaxSpeed, bMinSpeed, pMinSpeed);

TEST_CASE("Testing functions in namespace triangles") {
  sf::Vertex v1{pos1()};
  sf::Vertex v2{pos3()};

  sf::VertexArray triangles(sf::Triangles, 3 * flock1.getFlockSize());

  SUBCASE("Testing triangles::createTriangles()") {
    triangles::createTriangles(flock1, triangles);

    CHECK(triangles[0].color == sf::Color::Blue);
    CHECK(triangles[1].color == sf::Color::Blue);
    CHECK(triangles[2].color == sf::Color::Blue);

    CHECK(triangles[0].position == v1.position + sf::Vector2f(0, -triangles::height / 2));
    CHECK(triangles[1].position == v1.position + sf::Vector2f(-triangles::base_width / 2, triangles::height / 2));
    CHECK(triangles[2].position == v1.position + sf::Vector2f(triangles::base_width / 2, triangles::height / 2));

    CHECK(triangles[6].color == sf::Color::Red);
    CHECK(triangles[7].color == sf::Color::Red);
    CHECK(triangles[8].color == sf::Color::Red);

    CHECK(triangles[6].position == v2.position + sf::Vector2f(0, -(triangles::height * 3 / 4)));
    CHECK(triangles[7].position ==
          v2.position + sf::Vector2f(-triangles::base_width * 3 / 4, triangles::height * 3 / 4));
    CHECK(triangles[8].position ==
          v2.position + sf::Vector2f(triangles::base_width * 3 / 4, triangles::height * 3 / 4));

    CHECK(static_cast<int>(triangles.getVertexCount()) == 4 * 3);
  }
  SUBCASE("Testing triangles::rotateTriangles()") {
    double theta1{2.5};
    double theta2{3.6};
    const point::Point b1_pos = b1->getPosition();
    const point::Point p1_pos = p1->getPosition();

    triangles::rotateTriangle(b1_pos, triangles, theta1, 0, true, 2);
    triangles::rotateTriangle(p1_pos, triangles, theta2, 0, false, 2);

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

    CHECK(!flock0.getBoidFlock().empty());
    CHECK(!flock0.getPredatorFlock().empty());
  }

  SUBCASE("Testing getters") {
    constexpr std::array<double, 5> default_params{0.1, 0.1, 0.004, 0.6, 0.008};
    const std::array<double, 5> params = flock1.getFlightParams();

    CHECK(flock1.getFlockSize() == 4);
    CHECK(flock1.getBoidsNum() == 2);
    CHECK(flock1.getPredatorsNum() == 2);

    CHECK(flock1.getBoidFlock() == boids);
    CHECK(flock1.getPredatorFlock() == predators);

    CHECK(params[0] == default_params[0]);
    CHECK(params[1] == default_params[1]);
    CHECK(params[2] == default_params[2]);
    CHECK(params[3] == doctest::Approx(default_params[3]));
    CHECK(params[4] == doctest::Approx(default_params[4]));
  }

  SUBCASE("Testing setFlightParams method") {
    std::istringstream input1("y\n5\n1\n6\n");
    std::istringstream input2("y\n0\n1\n0.2\n");
    std::istringstream input3("-1\n");
    std::istringstream input4("n\n");

    std::ostringstream output1;
    std::ostringstream output2;
    std::ostringstream output3;
    std::ostringstream output4;

    CHECK_THROWS_WITH_AS(flock1.setFlightParams(input1, output1),
                         "Error: Invalid input. The program will now terminate.", std::domain_error);

    flock1.setFlightParams(input2, output2);
    std::array<double, 5> params = flock1.getFlightParams();

    CHECK(params[0] == 0);
    CHECK(params[1] == 1);
    CHECK(params[2] == 0.2);
    CHECK(params[0] == doctest::Approx(0));

    CHECK_THROWS_WITH_AS(flock1.setFlightParams(input3, output3),
                         "Error: Invalid input. The program will now terminate.", std::domain_error);

    flock1.setFlightParams(input4, output4);
    params = flock1.getFlightParams();

    CHECK(params[0] == 0);
    CHECK(params[1] == 1);
    CHECK(params[2] == 0.2);
    CHECK(params[3] == doctest::Approx(0));
    CHECK(params[4] == doctest::Approx(0.4));
  }

  SUBCASE("Testing findNearBoids method") {
    std::vector<std::shared_ptr<bird::Bird>> nearBoids1;
    nearBoids1 = flock1.findNearBoids(0, true);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearBoids1[0].get() == b2.get());

    std::vector<std::shared_ptr<bird::Bird>> nearBoids2;
    nearBoids2 = flock1.findNearBoids(0, false);

    CHECK(nearBoids2.size() == 1);
    CHECK(nearBoids2[0] == b1);
  }

  SUBCASE("Testing findNearPredators method") {
    std::vector<std::shared_ptr<bird::Bird>> nearPredators1;
    nearPredators1 = flock1.findNearPredators(0, true);

    CHECK(nearPredators1.size() == 2);
    CHECK(nearPredators1[0] == p1);
    CHECK(nearPredators1[1] == p2);

    std::vector<std::shared_ptr<bird::Bird>> nearPredators2;
    nearPredators2 = flock1.findNearPredators(0, false);

    CHECK(nearPredators2.size() == 1);
    CHECK(nearPredators2[0] == p2);

    flock::Flock flock2(2, 0);
    std::vector<std::shared_ptr<bird::Bird>> f2;
    f2.emplace_back(b1);
    f2.emplace_back(b2);

    CHECK(flock2.findNearPredators(0, true).empty());
  }

  std::array<point::Point, 2> update_boid = flock1.updateBird(triangles, 0, true);
  std::array<point::Point, 2> update_predator = flock1.updateBird(triangles, 0, false);

  SUBCASE("Testing updateBird method") {
    std::istringstream input0("n");
    std::ostringstream output0;
    flock1.setFlightParams(input0, output0);

    std::array<double, 5> params = flock1.getFlightParams();

    const double turnFactor = flock::Flock::getTurnFactor();
    const double margin = flock::Flock::getMargin();

    CHECK(turnFactor > 0);
    CHECK(margin < (graphic_par::window_width - graphic_par::stats_width) * 0.5);
    CHECK(margin < graphic_par::window_height * 0.5);

    std::vector<std::shared_ptr<bird::Bird>> nearBoids1;
    std::vector<std::shared_ptr<bird::Bird>> nearPredators1;
    nearBoids1 = flock1.findNearBoids(0, true);
    nearPredators1 = flock1.findNearPredators(0, true);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearPredators1.size() == 2);

    point::Point v_boid = b1->border(margin, turnFactor) + b1->repel(params[3], nearPredators1) +
                          b1->separation(params[0], b_ds, nearBoids1) + b1->alignment(params[1], nearBoids1) +
                          b1->cohesion(params[2], nearBoids1);
    b1->boost(bMinSpeed, v_boid);
    b1->friction(bMaxSpeed, v_boid);
    point::Point p_boid = b1->getPosition() + graphic_par::dt * v_boid;

    CHECK(update_boid[0].getX() == doctest::Approx(p_boid.getX()));
    CHECK(update_boid[0].getY() == doctest::Approx(p_boid.getY()));
    CHECK(update_boid[1].getX() == doctest::Approx(v_boid.getX()));
    CHECK(update_boid[1].getY() == doctest::Approx(v_boid.getY()));

    std::vector<std::shared_ptr<bird::Bird>> nearBoids2;
    std::vector<std::shared_ptr<bird::Bird>> nearPredators2;
    nearBoids2 = flock1.findNearBoids(0, false);
    nearPredators2 = flock1.findNearPredators(0, false);

    CHECK(nearBoids1.size() == 1);
    CHECK(nearPredators1.size() == 2);

    point::Point v_predator = p1->border(margin, turnFactor) + p1->separation(params[0], p_ds, nearPredators2) +
                              p1->chase(params[4], nearBoids2);

    p1->boost(pMinSpeed, v_predator);
    p1->friction(pMaxSpeed, v_predator);
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

    CHECK(flock1.getBoidFlock()[0]->getPosition().getX() == boid.getPosition().getX());
    CHECK(flock1.getBoidFlock()[0]->getPosition().getY() == boid.getPosition().getY());
    CHECK(flock1.getBoidFlock()[0]->getVelocity().getX() == boid.getVelocity().getX());
    CHECK(flock1.getBoidFlock()[0]->getVelocity().getY() == boid.getVelocity().getY());

    CHECK(triangles[0].color == sf::Color::Blue);
    CHECK(triangles[1].color == sf::Color::Blue);
    CHECK(triangles[2].color == sf::Color::Blue);

    CHECK(flock1.getPredatorFlock()[0]->getPosition().getX() == predator.getPosition().getX());
    CHECK(flock1.getPredatorFlock()[0]->getPosition().getY() == predator.getPosition().getY());
    CHECK(flock1.getPredatorFlock()[0]->getVelocity().getX() == predator.getVelocity().getX());
    CHECK(flock1.getPredatorFlock()[0]->getVelocity().getY() == predator.getVelocity().getY());

    CHECK(triangles[6].color == sf::Color::Red);
    CHECK(triangles[7].color == sf::Color::Red);
    CHECK(triangles[8].color == sf::Color::Red);
  }

  SUBCASE("Testing statistics method") {
    statistics::Statistics stats = flock1.statistics();

    CHECK(flock1.getBoidsNum() > 1);

    double speed1 = flock1.getBoidFlock()[0]->getVelocity().module();
    double speed2 = flock1.getBoidFlock()[1]->getVelocity().module();

    double mean_speed = (speed1 + speed2) / 2.;
    double mean_speed2 = (speed1 * speed1 + speed2 * speed2) / 2.;

    CHECK(stats.mean_dist ==
          doctest::Approx(flock1.getBoidFlock()[0]->getPosition().distance(flock1.getBoidFlock()[1]->getPosition())));
    CHECK(stats.mean_speed == doctest::Approx(mean_speed));
    CHECK(stats.dev_dist == doctest::Approx(0.));
    CHECK(stats.dev_speed == doctest::Approx(std::sqrt(mean_speed2 - mean_speed * mean_speed)));
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
