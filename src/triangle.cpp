#include "../include/triangle.hpp"

#include <cassert>
#include <cmath>

#include "../include/flock.hpp"
#include "../include/graphic.hpp"

namespace triangles {
void createTriangles(const flock::Flock& flock, sf::VertexArray& triangles) {
  for (int i = 0; i < flock.getBoidsNum(); ++i) {
    const int j = 3 * i;
    sf::Vertex vertex{flock.getBoidFlock()[i]->getPosition()()};

    // upper vertex (centered)
    triangles[j].position = vertex.position + sf::Vector2f(0, -height / 2);
    triangles[j].color = sf::Color::Blue;

    // down-left vertex
    triangles[j + 1].position = vertex.position + sf::Vector2f(-base_width / 2, height / 2);
    triangles[j + 1].color = sf::Color::Blue;

    // down-right vertex
    triangles[j + 2].position = vertex.position + sf::Vector2f(base_width / 2, height / 2);
    triangles[j + 2].color = sf::Color::Blue;
  }

  if (flock.getPredatorsNum() > 0) {
    for (int i = 0; i < flock.getPredatorsNum(); ++i) {
      sf::Vertex vertex{flock.getPredatorFlock()[i]->getPosition()()};

      const int j = 3 * (i + flock.getBoidsNum());
      // upper vertex (centered)
      triangles[j].position = vertex.position + sf::Vector2f(0, -(height * 1.5) / 2);
      triangles[j].color = sf::Color::Red;

      // down-left vertex
      triangles[j + 1].position = vertex.position + sf::Vector2f(-(base_width * 1.5) / 2, (height * 1.5) / 2);
      triangles[j + 1].color = sf::Color::Red;

      // down-right vertex
      triangles[j + 2].position = vertex.position + sf::Vector2f((base_width * 1.5) / 2, (height * 1.5) / 2);
      triangles[j + 2].color = sf::Color::Red;
    }
  }
  assert(static_cast<int>(triangles.getVertexCount()) == flock.getFlockSize() * 3);
}

void rotateTriangle(const point::Point& target_position, sf::VertexArray& triangles, const double theta, const int i,
                    const bool is_boid, const int nBoids) {
  const sf::Vertex vertex{target_position()};

  const int j = is_boid ? 3 * i : 3 * (i + nBoids);

  for (int k = j; k < j + 3; ++k) {
    const int index = is_boid ? k - j : k - j + 3;
    triangles[k].position =
        vertex.position + sf::Vector2f(static_cast<float>(relative_position[index].x * std::cos(theta) -
                                                          relative_position[index].y * std::sin(theta)),
                                       static_cast<float>(relative_position[index].x * std::sin(theta) +
                                                          relative_position[index].y * std::cos(theta)));
  }
}

float getBaseWidth() { return base_width; }
float getHeight() { return height; }
}  // namespace triangles
