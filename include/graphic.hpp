#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "../include/bird.hpp"
#include "../include/flock.hpp"

//----------------------------------------------------------------------------------------------------------------------
//---NAMESPACE GRAPHIC_PAR----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace graphic_par {

///@param dt It represents the temporal interval used to update cinematic quantities.
constexpr double dt = 0.7;

///@param windowWidth It represents the width of the simulation window.
constexpr float windowWidth = 1900.f;

///@param windowHeight It represents the height of the simulation window.
constexpr float windowHeight = 900.f;

///@param statsWidth It represents the width of the window containing the statistics data.
constexpr float statsWidth = 0.25 * windowWidth;

///@param maxVel_x It represents the upper boundary of the random generation range for the component x of the velocity
/// of a bird.
constexpr double maxVel_x = 5.;

///@param minVel_x It represents the lower boundary of the random generation range for the component x of the velocity
/// of a bird.
constexpr double minVel_x = -maxVel_x;

///@param maxVel_y It represents the upper boundary of the random generation range for the component y of the velocity
/// of a bird.
constexpr double maxVel_y = 3;

///@param minVel_y It represents the lower boundary of the random generation range for the component y of the velocity
/// of a bird.
constexpr double minVel_y = -maxVel_y;

///@brief It takes in input an integer, checking if it should be strictly positive or just positive. It allows 3
/// attempts to insert a valid input, then it exit the program.
///@param prompt Is a constant string that will be streamed in output.
///@param positive Is a boolean constant that determine if the output of the function should be strictly positive or
/// just positive.
///@return An integer.
int getPositiveInteger(const std::string& prompt, bool positive);
}  // namespace graphic_par

//----------------------------------------------------------------------------------------------------------------------
//---NAMESPACE TRIANGLES------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace triangles {

///@param baseWidth_ Represents the length of the triangle's base.
constexpr float baseWidth = 7;

///@param height Represents the height of the triangle.
constexpr float height = 15;

///@param relativePosition Is an array containing the relative position of a triangle's vertex in relation to the
/// center. The first three elements identify a triangle associated with a Boid object, the last three identify a
/// triangle associated with a Predator object.
const sf::Vector2f relativePosition[6] = {sf::Vector2f(0, -height / 2),
                                          sf::Vector2f(-baseWidth / 2, height / 2),
                                          sf::Vector2f(baseWidth / 2, height / 2),
                                          sf::Vector2f(0, (-height * 3 / 2) / 2),
                                          sf::Vector2f((-baseWidth * 3 / 2) / 2, (height * 3 / 2) / 2),
                                          sf::Vector2f((baseWidth * 3 / 2) / 2, (height * 3 / 2) / 2)};

/// @brief Construct an array of sf::Vertex, three to three represent triangles, one for each bird.
/// @param flock Is the vector of birds.
/// @param triangles Is an array containing tree sf::Vertex for each bird in the flock, those constitute a sf::Triangle.
void createTriangles(const flock::Flock& flock, sf::VertexArray& triangles);

/// @brief Update the direction of the triangle.
/// @details Rotate the triangle associated with the bird, according to the direction of the bird's velocity.
/// @param bird Is the bird associated with the triangle we need to rotate.
/// @param triangles Is an array containing tree sf::Vertex for each bird in the flock, those constitute a sf::Triangle.
/// @param theta Is the angle of the bird's updated velocity, formed with the vertical axis.
/// @param i Is the index associated with the position of the bird in the flock.
void rotateTriangle(const std::shared_ptr<bird::Bird>& bird, sf::VertexArray& triangles, double theta, int i);

/// @brief Get the base width of the triangle.
/// @return The base of the triangle.
[[nodiscard]] float getBaseWidth();

/// @brief Get the height of the triangle.
/// @return The height of the triangle.
[[nodiscard]] float getHeight();
}  // namespace triangles

#endif
