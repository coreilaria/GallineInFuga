#include "../include/graphic.hpp"

#include <cmath>
namespace triangles {
sf::VertexArray createTriangle(std::shared_ptr<Bird>& bird) {
  sf::Vertex vertex{bird->get_position()()};  // l'operatore () restituisce la conversione da Point a sf::Vertex
  sf::VertexArray triangle(sf::Triangles, 3);

  if (dynamic_cast<Boid*>(bird.get())) {
    triangle[0].position = vertex.position + sf::Vector2f(0, -height_ / 2);  // Vertice superiore (centrato)
    triangle[1].position = vertex.position + sf::Vector2f(-baseWidth_ / 2, height_ / 2);  // Vertice in basso a sinistra
    triangle[2].position = vertex.position + sf::Vector2f(baseWidth_ / 2, height_ / 2);   // Vertice in basso a destra

  } 
   if (dynamic_cast<Predator*>(bird.get())) {
    triangle[0].position = vertex.position + sf::Vector2f(0, -(height_ + 2) / 2);  // Vertice superiore (centrato)
    triangle[1].position =
        vertex.position + sf::Vector2f(-(baseWidth_ + 2) / 2, (height_ + 2) / 2);  // Vertice in basso a sinistra
    triangle[2].position =
        vertex.position + sf::Vector2f((baseWidth_ + 2) / 2, (height_ + 2) / 2);  // Vertice in basso a destra
  }
  return triangle;
}

void rotateTriangle(std::shared_ptr<Bird>& bird, sf::VertexArray& triangle, double delta_theta) {
  sf::Vertex vertex{bird->get_position()()};  // l'operatore () restituisce la conversione da Point a sf::Vertex

  for (int i = 0; i < 3; ++i) {
    const sf::Vector2f& pos =
        triangle[i].position -
        vertex
            .position;  // Posizione relativa al centro, alias (necessaria const reference poichè è oggetto temporaneo)
    triangle[i].position =
        vertex.position + sf::Vector2f(pos.x * std::cos(delta_theta) - pos.y * std::sin(delta_theta),
                                       pos.x * std::sin(delta_theta) + pos.y * std::cos(delta_theta));
  }
}
};  // namespace triangles
