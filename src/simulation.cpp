#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "../include/boid.hpp"
#include "../include/flock.hpp"
#include "../include/namespace.hpp"
#include "../include/point.hpp"
#include "../include/quadtree.hpp"

using namespace graphic_par;

int main() {
  Flock flock;
  flock.generateBoid();
  // flock.print();

  sf::RenderWindow window({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)},
                          "Flock simulation", sf::Style::Titlebar);
  window.setFramerateLimit(60);
  sf::Event event{};

  sf::VertexBuffer points{sf::Points};
  points.create(flock.get_size());
  points.setUsage(sf::VertexBuffer::Usage::Dynamic);

  std::vector<sf::Vertex> vertices(flock.get_size());

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    std::vector<sf::VertexArray> triangles = flock.createTriangle(vertices);

    window.clear();
    for (auto& triangle : triangles) {
      window.draw(triangle);  // Draw each triangle directly
    }
    
    window.display();

    flock.evolve();
  }
}
