#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <SFML/Graphics/VertexArray.hpp>

#include "../include/bird.hpp"
#include "../include/flock.hpp"

namespace triangles {

inline constexpr float base_width = 7;
inline constexpr float height = 15;

///@brief Array containing the relative position of a triangle's vertex in relation to the
/// center. The first three elements identify a triangle associated with a bird::Boid object, the last three identify a
/// triangle associated with a bird::Predator object.
inline const std::array<sf::Vector2f, 6> relative_position = {
    sf::Vector2f(0, -height / 2),
    sf::Vector2f(-base_width / 2, height / 2),
    sf::Vector2f(base_width / 2, height / 2),
    sf::Vector2f(0, (-height * 3 / 2) / 2),
    sf::Vector2f((-base_width * 3 / 2) / 2, (height * 3 / 2) / 2),
    sf::Vector2f((base_width * 3 / 2) / 2, (height * 3 / 2) / 2)};

/// @brief Constructs an array of sf::Vertex, three to three represent a triangle which is associated with a single
/// bird.
/// @param flock Is the vector of birds.
/// @param triangles Is an array containing three sf::Vertex for each bird in the flock, those constitute a
/// sf::Triangle.
void createTriangles(const flock::Flock& flock, sf::VertexArray& triangles);

/// @brief Updates the direction of the triangle.
/// @details Rotates the triangle associated with the bird, according to the direction of the bird's velocity.
/// @param target_position Is the position of the current bird.
/// @param triangles Is an array containing three sf::Vertex for each bird in the flock, those constitute a
/// sf::Triangle.
/// @param theta Is the angle of the bird's updated velocity, formed with the vertical axis.
/// @param i Is the index associated with the position of the bird in the flock.
/// @param is_boid Is a boolean constant which states whether the current bird is a bird::Boid or a bird::Predator.
/// @param nBoids Is the number of bird::Boid objects in the flock.
void rotateTriangle(const point::Point& target_position, sf::VertexArray& triangles, double theta, size_t i,
                    bool is_boid, size_t nBoids);
}  // namespace triangles

#endif  // TRIANGLE_HPP
