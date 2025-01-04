#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>

#include "../include/flock.hpp"
#include "../include/graphic.hpp"

using namespace graphic_par;
using namespace triangles;

int main() {
  int nBoid = getPositiveInteger("Enter the number of boids to simulate: ", true);
  int nPredator = getPositiveInteger("Enter the number of predators to simulate: ", false);

  flock::Flock flock(nBoid, nPredator);

  statistics::Statistics statistics;
  flock.generateBirds();
  unsigned int counter{0};

  sf::VertexArray triangles(sf::Triangles, 3 * (flock.getFlockSize()));
  createTriangles(flock, triangles);

  sf::VertexBuffer rectangle{sf::TriangleStrip, sf::VertexBuffer::Usage::Static};
  sf::Vertex v[4] = {sf::Vertex(sf::Vector2f(0., 0.)), sf::Vertex(sf::Vector2f(0., windowHeight)),
                     sf::Vertex(sf::Vector2f(statsWidth, 0.)), sf::Vertex(sf::Vector2f(statsWidth, windowHeight))};
  for (auto& i : v) {
    i.color = sf::Color(50, 50, 50);
  }
  rectangle.create(4);
  rectangle.update(v);

  sf::RenderWindow window({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)},
                          "Flock simulation", sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(10, 50));
  window.setFramerateLimit(60);
  sf::Event event{};

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

    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("arial.ttf")) {
      std::cerr << "Error: Fail to load the font.\n";
      return -1;
    }

    text.setFont(font);
    text.setPosition(sf::Vector2f(10, 10));

    std::string text_display;

    if (counter % 15 == 0) {
      statistics = flock.statistics();
    }
    text_display = "Mean distance: " + std::to_string(statistics.dev_dist) + "\n" +
                   "Distance standard deviation: " + std::to_string(statistics.dev_dist) + "\n\n" +
                   "Mean speed: " + std::to_string(statistics.mean_speed) + "\n" +
                   "Speed standard deviation: " + std::to_string(statistics.dev_speed);
    text.setString(text_display);
    text.setCharacterSize(24);  // in pixels
    text.setFillColor(sf::Color::White);

    ++counter;  // might overflow, it would restart from 0, which is compatible with the logic of the program.
    window.clear();

    flock.evolve(triangles);

    window.draw(triangles);
    window.draw(rectangle);
    window.draw(text);

    window.display();
  }
}
