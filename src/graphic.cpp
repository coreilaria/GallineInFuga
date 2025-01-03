#include "../include/graphic.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

#include "../include/flock.hpp"
namespace graphic_par {
int getPositiveInteger(const std::string& prompt, bool const positive) {
  int value;
  int counter{0};
  while (counter < 3) {
    std::cout << prompt;
    std::cin >> value;

    // check if the input is valid
    if (std::cin.fail() || (positive && value <= 0)) {
      std::cin.clear();                                                    // clear the error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
      if (positive) {
        std::cout << "Invalid input! Please enter a positive integer.\n\n";
      } else {
        std::cout << "Invalid input! Please enter an integer.\n\n";
      }
      counter++;
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear the buffer
      return value;
    }
  }

  std::cout << "\nToo many invalid input. The program will now terminate.\n";
  exit(1);  // Termina il programma
}

}  // namespace graphic_par
namespace triangles {
void createTriangles(const flock::Flock& flock, sf::VertexArray& triangles) {
  for (int i = 0; i < flock.getFlockSize(); ++i) {
    const int j = 3 * i;
    sf::Vertex vertex{flock.getFlock()[i]->getPosition()()};  // operator () returns conversion from Point to sf::Vertex

    if (i < flock.getBoidsNum()) {
      // upper vertex (centered)
      triangles[j].position = vertex.position + sf::Vector2f(0, -height_ / 2);
      triangles[j].color = sf::Color::Blue;

      // down-left vertex
      triangles[j + 1].position = vertex.position + sf::Vector2f(-baseWidth_ / 2, height_ / 2);
      triangles[j + 1].color = sf::Color::Blue;

      // down-right vertex
      triangles[j + 2].position = vertex.position + sf::Vector2f(baseWidth_ / 2, height_ / 2);
      triangles[j + 2].color = sf::Color::Blue;

    } else {
      // upper vertex (centered)
      triangles[j].position = vertex.position + sf::Vector2f(0, -(height_ * 3 / 2) / 2);
      triangles[j].color = sf::Color::Red;

      // down-left vertex
      triangles[j + 1].position = vertex.position + sf::Vector2f(-(baseWidth_ * 3 / 2) / 2, (height_ * 3 / 2) / 2);
      triangles[j + 1].color = sf::Color::Red;

      // down-right vertex
      triangles[j + 2].position = vertex.position + sf::Vector2f((baseWidth_ * 3 / 2) / 2, (height_ * 3 / 2) / 2);
      triangles[j + 2].color = sf::Color::Red;
    }
  }
  assert(static_cast<int>(triangles.getVertexCount()) == flock.getFlockSize() * 3);
}

void rotateTriangle(const std::shared_ptr<Bird>& bird, sf::VertexArray& triangle, const double theta, const int i) {
  const sf::Vertex vertex{bird->getPosition()()};  // operator () returns conversion from Point to sf::Vertex

  const int j = 3 * i;

  for (int k = j; k < j + 3; ++k) {
    if (std::dynamic_pointer_cast<Boid>(bird)) {
      triangle[k].position =
          vertex.position + sf::Vector2f(static_cast<float>(relative_position[k - j].x * std::cos(theta) -
                                                            relative_position[k - j].y * std::sin(theta)),
                                         static_cast<float>(relative_position[k - j].x * std::sin(theta) +
                                                            relative_position[k - j].y * std::cos(theta)));
    } else if (std::dynamic_pointer_cast<Predator>(bird)) {
      triangle[k].position =
          vertex.position + sf::Vector2f(static_cast<float>(relative_position[k - j + 3].x * std::cos(theta) -
                                                            relative_position[k - j + 3].y * std::sin(theta)),
                                         static_cast<float>(relative_position[k - j + 3].x * std::sin(theta) +
                                                            relative_position[k - j + 3].y * std::cos(theta)));
    }
  }
}

float getBaseWidth() { return baseWidth_; }
float getHeight() { return height_; }
}  // namespace triangles
