#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "../include/boid.hpp"
#include "../include/constants.hpp"
#include "../include/point.hpp"
#include "../include/quadtree.hpp"
#include "../include/sfml.hpp"
#include "../include/flock.hpp"

using namespace graphic_par;

int main() {

  Flock flock;
  flock.generateBoid();
  flock.print();
  
  sf::RenderWindow window({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)},
                          "Flock simulation", sf::Style::Titlebar);
  window.setFramerateLimit(60);
  sf::Event event{};

  // // sf::VertexBuffer Margin{sf::Lines};
  // // Margin.create(8);
  // // Margin.setUsage(sf::VertexBuffer::Usage::Static);
  // // Margin.update(std::array<sf::Vertex, 8>{
  // //       sf::Vertex({margin, margin}), sf::Vertex({windowWidth - margin, margin}),
  // //       sf::Vertex({margin, margin}), sf::Vertex({margin, windowHeight - margin}),
  // //       sf::Vertex({windowWidth - margin, margin}), sf::Vertex({windowWidth - margin, windowHeight - margin}),
  // //       sf::Vertex({margin, windowHeight - margin}), sf::Vertex({windowWidth - margin, windowHeight - margin}),

  //   }.data()); 

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

    flock.vertex(vertices);

    // .data() ritorna il puntatore all'array nativo sotto std::array
    points.update(vertices.data());

    window.clear();

    window.draw(points); // BUFFER
    // window.draw(Margin);  

    window.display();

    flock.evolve();
  }
}
