#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

#include "../include/boid.hpp"
#include "../include/flock.hpp"
#include "../include/namespace.hpp"
#include "../include/point.hpp"
#include "../include/quadtree.hpp"

using namespace graphic_par;

int main() {
  Flock flock;
  Statistics statistics;
  flock.generateBoid();
  // flock.print();

  sf::RenderWindow window({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)},
                          "Flock simulation", sf::Style::Titlebar);


  window.setPosition(sf::Vector2i(10, 50));
  window.setFramerateLimit(60);
  //this feature is implemented by SFML itself, using a combination of sf::Clock and sf::sleep. 
  //An important consequence is that it is not 100% reliable, 
  //especially for high framerates: sf::sleep's resolution depends on the underlying operating system and hardware, 
  //and can be as high as 10 or 15 milliseconds. Don't rely on this feature to implement precise timing.
  
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

    statistics = flock.statistics();
    std::vector<sf::VertexArray> triangles = flock.createTriangle(vertices);

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
      // da pensare a come gestire
    }
    text.setFont(font);
    std::string mean_distance;
    std::string mean_speed;
    std::string dev_distance;
    std::string dev_speed;

    mean_distance = "Mean distance: " + std::to_string(statistics[0]);
    dev_distance = "Dinstance standard deviation: " + std::to_string(statistics[1]);
    mean_speed = "Mean speed: " + std::to_string(statistics[2]);
    dev_distance = "Speed standard deviation: " + std::to_string(statistics[3]);

    text.setString(mean_distance);
    text.setString(dev_distance);
    text.setString(mean_speed);
    text.setString(dev_speed);

    text.setCharacterSize(24);  // in pixels

    text.setFillColor(sf::Color::White);

    // set the text style
    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.clear();
    for (auto& triangle : triangles) {
      window.draw(triangle);  // Draw each triangle directly
    }
    window.draw(text);

    window.display();

    flock.evolve();
  }
}
