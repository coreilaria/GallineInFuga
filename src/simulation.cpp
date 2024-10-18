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

int main() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist_pos(minPos, maxPos);
  std::uniform_real_distribution<double> dist_vel(minVel, maxVel);

  std::vector<Boid> flock(N);
  std::vector<Boid> flock_out(N);

  std::generate(flock.begin(), flock.end(),
                [&]() { return Boid(Point(dist_pos(rng), dist_pos(rng)), Point(dist_vel(rng), dist_vel(rng))); });

  // int c = 0;

  sf::RenderWindow window({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)},
                          "flock simulation", sf::Style::Titlebar);
  window.setFramerateLimit(60);
  sf::Event event{};

  sf::VertexBuffer points{sf::Points};
  points.create(N);
  points.setUsage(sf::VertexBuffer::Usage::Dynamic);

  std::vector<sf::Vertex> vertices(N);

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

    std::for_each(flock.begin(), flock.end(), [&, i = 0](Boid &boid) mutable {
      vertices[i] = boid.get_position()();
      toSfmlCoord(vertices[i]);
      ++i;
    });

    // .data() ritorna il puntatore all'array nativo sotto std::array
    points.update(vertices.data());

    window.clear();

    window.draw(points);  // BUFFER

    window.display();

    Boid::evolve(flock);
  }
}
