#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>

#include "../include/bird.hpp"
#include "../include/flock.hpp"


//----------------------------------------------------------------------------------------------------------------------
//---NAMESPACE TRIANGLES------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace triangles {

///@param base_width Represents the length of the triangle's base.
constexpr float base_width = 7;

///@param height Represents the height of the triangle.
constexpr float height = 15;

///@param relative_position Is an array containing the relative position of a triangle's vertex in relation to the
/// center. The first three elements identify a triangle associated with a bird::Boid object, the last three identify a
/// triangle associated with a bird::Predator object.
const std::array<sf::Vector2f, 6> relative_position = {sf::Vector2f(0, -height / 2),
                                                       sf::Vector2f(-base_width / 2, height / 2),
                                                       sf::Vector2f(base_width / 2, height / 2),
                                                       sf::Vector2f(0, (-height * 3 / 2) / 2),
                                                       sf::Vector2f((-base_width * 3 / 2) / 2, (height * 3 / 2) / 2),
                                                       sf::Vector2f((base_width * 3 / 2) / 2, (height * 3 / 2) / 2)};

/// @brief Constructs an array of sf::Vertex, three to three represent triangles, one for each bird.
/// @param flock Is the vector of birds.
/// @param triangles Is an array containing tree sf::Vertex for each bird in the flock, those constitute a sf::Triangle.
void createTriangles(const flock::Flock& flock, sf::VertexArray& triangles);

/// @brief Updates the direction of the triangle.
/// @details Rotates the triangle associated with the bird, according to the direction of the bird's velocity.
/// @param bird Is the bird associated with the triangle we need to rotate.
/// @param triangles Is an array containing tree sf::Vertex for each bird in the flock, those constitute a sf::Triangle.
/// @param theta Is the angle of the bird's updated velocity, formed with the vertical axis.
/// @param i Is the index associated with the position of the bird in the flock.
void rotateTriangle(const std::shared_ptr<bird::Bird>& bird, sf::VertexArray& triangles, double theta, int i);

/// @brief Gets the base width of the triangle.
/// @return The base width of the triangle.
[[nodiscard]] float getBaseWidth();

/// @brief Gets the height of the triangle.
/// @return The height of the triangle.
[[nodiscard]] float getHeight();
}  // namespace triangles


#endif //TRIANGLE_HPP
