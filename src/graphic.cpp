#include "../include/graphic.hpp"

#include <sstream>
#include <stdexcept>

#include "../include/flock.hpp"
namespace graphic_par {

sf::VertexBuffer createRectangle(std::array<sf::Vertex, 4>& vertex, const unsigned char red, const unsigned char green,
                                 const unsigned char blue) {
  for (auto& v : vertex) {
    v.color = sf::Color(red, green, blue);
  }
  sf::VertexBuffer rectangle(sf::TriangleStrip, sf::VertexBuffer::Static);

  if (!rectangle.create(4)) {
    throw std::runtime_error("Failed to create VertexBuffer.");
  }

  if (!rectangle.update(vertex.data())) {
    throw std::runtime_error("Failed to update VertexBuffer.");
  }

  return rectangle;
}

size_t getPositiveInteger(const std::string& prompt, std::istream& in, std::ostream& out, const bool positive) {
  int value;
  out << prompt;
  in >> value;

  if (in.fail()) {
    throw std::runtime_error("Input failed.");
  }

  if (positive && value <= 0) {
    throw std::domain_error("Error: Invalid input. The program will now terminate.");
  }
  return static_cast<size_t>(value);
}

double getPositiveDouble(const std::string& prompt, std::istream& in, std::ostream& out) {
  double value;
  out << prompt;
  in >> value;

  if (in.fail()) {
    throw std::runtime_error("Input failed.");
  }

  if (value < 0 || value > 1) {
    throw std::domain_error("Error: Invalid input. The program will now terminate.");
  }
  return value;
}

}  // namespace graphic_par