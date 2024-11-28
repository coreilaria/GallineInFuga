#include "../include/graphic.hpp"

#include <cmath>

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
      triangles[j+1].color = sf::Color::Blue;

      triangles[j + 2].position =
          vertex.position + sf::Vector2f(baseWidth_ / 2, height_ / 2);  // Vertice in basso a destra
      triangles[j+2].color = sf::Color::Blue;

    } else {
      triangles[j].position = vertex.position + sf::Vector2f(0, -(height_ + 2) / 2);  // Vertice superiore (centrato)
      triangles[j].color = sf::Color::Red;

      triangles[j + 1].position =
          vertex.position + sf::Vector2f(-(baseWidth_ + 2) / 2, (height_ + 2) / 2);  // Vertice in basso a sinistra
      triangles[j+1].color = sf::Color::Red;

      triangles[j + 2].position =
          vertex.position + sf::Vector2f((baseWidth_ + 2) / 2, (height_ + 2) / 2);  // Vertice in basso a destra
      triangles[j+2].color = sf::Color::Red;

    }
  }
}

void rotateTriangle(const std::shared_ptr<Bird>& bird, sf::VertexArray& triangle, const double delta_theta,
                    const int i) {
  const sf::Vertex vertex{bird->get_position()()};  // l'operatore () restituisce la conversione da Point a sf::Vertex

  // for (int j = 3 * i; j < 3 * i + 3; ++j) {
  //   const sf::Vector2f pos = triangle[j].position - vertex.position;  // Posizione relativa al centro
  //   triangle[j].position =
  //       vertex.position + sf::Vector2f(pos.x * std::cos(delta_theta) - pos.y * std::sin(delta_theta),
  //                                      pos.x * std::sin(delta_theta) + pos.y * std::cos(delta_theta));
  // }
const double theta = bird->get_velocity().angle();
  for (int j = 3 * i; j < 3 * i + 3; ++j) {
    const sf::Vector2f pos = triangle[j].position - vertex.position;  // Posizione relativa al centro
    triangle[j].position =
        vertex.position + sf::Vector2f(pos.x * std::cos(theta) - pos.y * std::sin(theta),
                                       pos.x * std::sin(theta) + pos.y * std::cos(theta));
  }
}
}  // namespace triangles
