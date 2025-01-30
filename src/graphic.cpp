#include "../include/graphic.hpp"

#include <cassert>
#include <cmath>
#include <sstream>

#include "../include/flock.hpp"
namespace graphic_par {

int getPositiveInteger(const std::string& prompt, std::istream& in, std::ostream& out, const bool positive) {
  int value;
  out << prompt;
  in >> value;

  // check if the input is valid
  if (in.fail() || (positive && value <= 0)) {
    in.clear();                                                    // clear the error flag
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
    out << "\nInvalid input. The program will now terminate.\n";
    exit(1);
  }
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear the buffer
  return value;
}

double getPositiveDouble(const std::string& prompt, std::istream& in, std::ostream& out) {
  double value;
  out << prompt;
  in >> value;

  if (in.fail() || (value < 0 || value > 1)) {
    in.clear();                                                    // clear the error flag
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
    out << "\nInvalid input. The program will now terminate.\n";
    exit(1);  // Use exceptions or return values in production code for better handling
  }
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear the buffer
  return value;
}

}  // namespace graphic_par