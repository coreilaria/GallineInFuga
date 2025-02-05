#include "../include/graphic.hpp"

#include <sstream>
#include <stdexcept>

#include "../include/flock.hpp"
namespace graphic_par {

size_t getPositiveInteger(const std::string& prompt, std::istream& in, std::ostream& out, const bool positive) {
  int value;
  out << prompt;
  in >> value;

  if (in.fail() || (positive && value <= 0)) {
    throw std::domain_error("Error: Invalid input. The program will now terminate.");
  }
  return static_cast<size_t>(value);
}

double getPositiveDouble(const std::string& prompt, std::istream& in, std::ostream& out) {
  double value;
  out << prompt;
  in >> value;
  if (in.fail() || (value < 0 || value > 1)) {
    throw std::domain_error("Error: Invalid input. The program will now terminate.");
  }
  return value;
}

}  // namespace graphic_par