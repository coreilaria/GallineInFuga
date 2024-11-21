#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../include/flock.hpp"
#include "../include/graphic.hpp"

using namespace graphic_par;

int main() {
  Flock flock;
  Statistics statistics;
  flock.generateBirds();
  
  if (flock.getFlockSize() == 0) {
    std::cerr << "fucks";
  } else {
    std::cout << "La size di flock è " << flock.getFlockSize();
  }
  std::vector<sf::VertexArray> triangles;

  unsigned int counter{0};
  sf::RectangleShape rectangle(sf::Vector2f(statsWidth, windowHeight));
  rectangle.setFillColor(sf::Color(50, 50, 50));
  rectangle.setPosition(sf::Vector2f(0., 0.));

  sf::RenderWindow window({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)},
                          "Flock simulation", sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(10, 50));
  window.setFramerateLimit(60);
  // this feature is implemented by SFML itself, using a combination of sf::Clock and sf::sleep.
  // An important consequence is that it is not 100% reliable,
  // especially for high framerates: sf::sleep's resolution depends on the underlying operating system and hardware,
  // and can be as high as 10 or 15 milliseconds. Don't rely on this feature to implement precise timing.

  sf::Event event{};

  sf::VertexBuffer points{sf::Points};
  points.create(flock.getFlockSize());
  points.setUsage(sf::VertexBuffer::Usage::Dynamic);
  std::vector<sf::Vertex> vertices(flock.getFlockSize());

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
    // PENSARE AD UN MODO INTELLIGENTE PER RIEMPIRE TRIANGLES

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("../arial.ttf")) {
      std::cerr << "Errore: Impossibile caricare il font.\n";
      return -1;
    }

    text.setFont(font);
    text.setPosition(sf::Vector2f(10, 10));

    std::string text_display;

    if (counter % 15 == 0) {
      statistics = flock.statistics();
    }
    text_display = "Mean distance: " + std::to_string(statistics.dev_dist) + "\n" +
                   "Dinstance standard deviation: " + std::to_string(statistics.dev_dist) + "\n\n" +
                   "Mean speed: " + std::to_string(statistics.mean_speed) + "\n" +
                   "Speed standard deviation: " + std::to_string(statistics.dev_speed);
    text.setString(text_display);
    text.setCharacterSize(24);  // in pixels
    text.setFillColor(sf::Color::White);

    // può fare overflow, essendo unsigned int ricomincia da 0 che è ok per la logica del programma
    ++counter;
    window.clear();

    for (auto& triangle : triangles) {
      window.draw(triangle);  // Draw each triangle directly
    }

    window.draw(points);
    window.draw(rectangle);
    window.draw(text);

    window.display();

    flock.evolve(triangles);
  }
}
