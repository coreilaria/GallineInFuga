#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "../include/bird.hpp"

namespace graphic_par {

///@param dt It represents the temporal interval used to update cinematic quantities.
inline constexpr double dt = 0.7;

///@param window_width It represents the width of the simulation window.
inline constexpr float window_width = 1900.f;

///@param window_height It represents the height of the simulation window.
inline constexpr float window_height = 900.f;

///@param stats_width It represents the width of the window containing the statistical data.
inline constexpr float stats_width = 0.25 * window_width;

///@param max_vel_x It represents the upper boundary of the random generation range for the component x of the velocity
/// of a bird::Boid or bird::Predator object.
inline constexpr double max_vel_x = 5.;

///@param min_vel_x It represents the lower boundary of the random generation range for the component x of the velocity
/// of a bird::Boid or bird::Predator object.
inline constexpr double min_vel_x = -max_vel_x;

///@param max_vel_y It represents the upper boundary of the random generation range for the component y of the velocity
/// of a bird::Boid or bird::Predator object.
inline constexpr double max_vel_y = 3;

///@param min_vel_y It represents the lower boundary of the random generation range for the component y of the velocity
/// of a bird::Boid or bird::Predator object.
inline constexpr double min_vel_y = -max_vel_y;

///@param stats_rectangle It's an array containing the vertexes needed to draw the statistics' rectangle from
/// sf::TrianglesStrips.
inline std::array<sf::Vertex, 4> stats_rectangle = {
    sf::Vertex(sf::Vector2f(0., 0.)), sf::Vertex(sf::Vector2f(0., window_height)),
    sf::Vertex(sf::Vector2f(stats_width, 0.)), sf::Vertex(sf::Vector2f(stats_width, window_height))};


///@brief It takes in input a double, checking if lays in the range [0,1]. If an invalid input is given, it exits the
/// program.
///@param vertex It is an array containing the vertexes needed to draw a rectangle from sf::TrianglesStrips.
///@param red It is the red rgb component.
///@param green It is the green rgb component.
///@param blue It is the blue rgb component.
///@return A sf::VertexBuffer.
sf::VertexBuffer createRectangle(std::array<sf::Vertex, 4>& vertex, unsigned char red, unsigned char green,
                                 unsigned char blue);

///@brief It takes in input an integer, checking if it should be strictly positive. If a valid input is given, the
/// number would be returned, otherwise the program will terminate.
///@param prompt Is a constant string that will be streamed in output.
///@param in Is the input stream.
///@param out Is the output stream.
///@param positive Is a boolean constant that determines if the output of the function should be strictly positive or
/// positive.
///@return A size_t value.
size_t getPositiveInteger(const std::string& prompt, std::istream& in, std::ostream& out, bool positive);

///@brief It takes in input a double, checking if it lays in the range [0,1]. If a valid input is given, the
/// number would be returned, otherwise the program will terminate.
///@param prompt Is a constant string that will be streamed in output.
///@param in Is the input stream.
///@param out Is the output stream.
///@return A double.
double getPositiveDouble(const std::string& prompt, std::istream& in, std::ostream& out);
}  // namespace graphic_par
#endif
