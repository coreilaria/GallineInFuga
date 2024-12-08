#include "../include/graphic.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

#include "../include/flock.hpp"
namespace triangles {
void createTriangles(const Flock& flock, sf::VertexArray& triangles) {
  for (int i = 0; i < flock.getFlockSize(); ++i) {
    const int j = 3 * i;
    sf::Vertex vertex{
        flock.getFlock()[i]->get_position()()};  // l'operatore () restituisce la conversione da Point a sf::Vertex

    if (i < flock.getBoidsNum()) {
      triangles[j].position = vertex.position + sf::Vector2f(0, -height_ / 2);  // Vertice superiore (centrato)
      triangles[j].color = sf::Color::Blue;
      triangles[j + 1].position =
          vertex.position + sf::Vector2f(-baseWidth_ / 2, height_ / 2);  // Vertice in basso a sinistra
      triangles[j + 1].color = sf::Color::Blue;

      triangles[j + 2].position =
          vertex.position + sf::Vector2f(baseWidth_ / 2, height_ / 2);  // Vertice in basso a destra
      triangles[j + 2].color = sf::Color::Blue;

    } else {
      triangles[j].position =
          vertex.position + sf::Vector2f(0, -(height_ * 3 / 2) / 2);  // Vertice superiore (centrato)
      triangles[j].color = sf::Color::Red;

      triangles[j + 1].position = vertex.position + sf::Vector2f(-(baseWidth_ * 3 / 2) / 2,
                                                                 (height_ * 3 / 2) / 2);  // Vertice in basso a sinistra
      triangles[j + 1].color = sf::Color::Red;

      triangles[j + 2].position =
          vertex.position + sf::Vector2f((baseWidth_ * 3 / 2) / 2, (height_ * 3 / 2) / 2);  // Vertice in basso a destra
      triangles[j + 2].color = sf::Color::Red;
    }
  }
  assert(triangles.getVertexCount() == flock.getFlockSize() * 3);
  for (auto& triangle : triangles) {
    assert(triangle != nullptr);
  }
}

void rotateTriangle(const std::shared_ptr<Bird>& bird, sf::VertexArray& triangle, const double delta_theta,
                    const int i) {
  const sf::Vertex vertex{bird->get_position()()};  // l'operatore () restituisce la conversione da Point a sf::Vertex

  const double theta = bird->get_velocity().angle();

  const sf::Vector2f relative_position[6] = {sf::Vector2f(0, -height_ / 2),
                                             sf::Vector2f(-baseWidth_ / 2, height_ / 2),
                                             sf::Vector2f(baseWidth_ / 2, height_ / 2),
                                             sf::Vector2f(0, (-height_ * 3 / 2) / 2),
                                             sf::Vector2f((-baseWidth_ * 3 / 2) / 2, (height_ * 3 / 2) / 2),
                                             sf::Vector2f((baseWidth_ * 3 / 2) / 2, (height_ * 3 / 2) / 2)};
  const int j = 3 * i;

  for (int k = j; k < j + 3; ++k) {
    if (std::dynamic_pointer_cast<Boid>(bird)) {
      triangle[k].position =
          vertex.position + sf::Vector2f(static_cast<float>(relative_position[k - j].x * std::cos(theta + delta_theta) -
                                             relative_position[k - j].y * std::sin(theta + delta_theta)),
                                         static_cast<float>(relative_position[k - j].x * std::sin(theta + delta_theta) +
                                             relative_position[k - j].y * std::cos(theta + delta_theta)));
    } else if (std::dynamic_pointer_cast<Predator>(bird)) {
      triangle[k].position =
          vertex.position + sf::Vector2f(static_cast<float>(relative_position[k - j + 3].x * std::cos(theta + delta_theta) -
                                             relative_position[k - j + 3].y * std::sin(theta + delta_theta)),
                                         static_cast<float>(relative_position[k - j + 3].x * std::sin(theta + delta_theta) +
                                             relative_position[k - j + 3].y * std::cos(theta + delta_theta)));
    }
  }
}
}  // namespace triangles
