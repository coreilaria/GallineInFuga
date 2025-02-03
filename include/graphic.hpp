#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "../include/bird.hpp"

//----------------------------------------------------------------------------------------------------------------------
//---NAMESPACE GRAPHIC_PAR----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace graphic_par {

///@param dt It represents the temporal interval used to update cinematic quantities.
constexpr double dt = 0.7;

///@param window_width It represents the width of the simulation window.
constexpr float window_width = 1900.f;

///@param window_height It represents the height of the simulation window.
constexpr float window_height = 900.f;

///@param stats_width It represents the width of the window containing the statistical data.
constexpr float stats_width = 0.25 * window_width;

///@param max_vel_x It represents the upper boundary of the random generation range for the component x of the velocity
/// of a bird::Boid or bird::Predator object.
constexpr double max_vel_x = 5.;

///@param min_vel_x It represents the lower boundary of the random generation range for the component x of the velocity
/// of a bird::Boid or bird::Predator object.
constexpr double min_vel_x = -max_vel_x;

///@param max_vel_y It represents the upper boundary of the random generation range for the component y of the velocity
/// of a bird::Boid or bird::Predator object.
constexpr double max_vel_y = 3;

///@param min_vel_y It represents the lower boundary of the random generation range for the component y of the velocity
/// of a bird::Boid or bird::Predator object.
constexpr double min_vel_y = -max_vel_y;

///@brief It takes in input an integer, checking if it should be strictly positive. If an invalid input is given, it
/// exits the program.
///@param prompt Is a constant string that will be streamed in output.
///@param in Is the input stream.
///@param out Is the output stream.
///@param positive Is a boolean constant that determines if the output of the function should be strictly positive or
/// just positive.
///@return An integer.
size_t getPositiveInteger(const std::string& prompt, std::istream& in, std::ostream& out, bool positive);

///@brief It takes in input a double, checking if it lays in the range [0,1]. If an invalid input is given, it exits the
/// program.
///@param prompt Is a constant string that will be streamed in output.
///@param in Is the input stream.
///@param out Is the output stream.
///@return A double.
double getPositiveDouble(const std::string& prompt, std::istream& in, std::ostream& out);

}  // namespace graphic_par
#endif
