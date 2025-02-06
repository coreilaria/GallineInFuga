#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/flock.hpp"
#include "../include/graphic.hpp"
#include "../include/triangle.hpp"

int main() {
  statistics::Statistics statistics;
  unsigned int counter{0};

  size_t nBoids = graphic_par::getPositiveInteger("Enter the number of boids to simulate: ", std::cin, std::cout, true);
  size_t nPredators =
      graphic_par::getPositiveInteger("Enter the number of predators to simulate: ", std::cin, std::cout, false);

  flock::Flock flock(nBoids, nPredators);
  flock.setFlightParams(std::cin, std::cout);

  flock.generateBirds();

  sf::VertexArray triangles(sf::Triangles, 3 * (flock.getFlockSize()));
  triangles::createTriangles(flock, triangles);

  sf::VertexBuffer stats_rectangle = graphic_par::createRectangle(graphic_par::stats_rectangle, 50, 50, 50);

  sf::RenderWindow window(
      {static_cast<unsigned int>(graphic_par::window_width), static_cast<unsigned int>(graphic_par::window_height)},
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

    std::ostringstream out;

    out << "Mean distance: " << std::fixed << std::setprecision(2) << statistics.mean_dist << "\n"
        << "Distance standard deviation: " << std::fixed << std::setprecision(2) << statistics.dev_dist << "\n\n"
        << "Mean speed: " << std::fixed << std::setprecision(2) << statistics.mean_speed << "\n"
        << "Speed standard deviation: " << std::fixed << std::setprecision(2) << statistics.dev_speed;

    text.setString(out.str());
    text.setCharacterSize(24);  // in pixels
    text.setFillColor(sf::Color::White);

    ++counter;  // might overflow, it would restart from 0, which is compatible with the logic of the program.
    window.clear();

    flock.evolve(triangles);

    window.draw(triangles);
    window.draw(stats_rectangle);
    window.draw(text);

    window.display();
  }
}
