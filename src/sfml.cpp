#include "../include/point.hpp"
#include "../include/boid.hpp"
#include "../include/sfml.hpp"
#include "../include/constants.hpp"

#include <SFML/Graphics.hpp>

using namespace graphic_par;


//il vertex è inizializzato con la posizione del boide in coordinate cartesiane
void toSfmlCoord(sf::Vertex &vertex){

    float &x = vertex.position.x; //ho creato un alias, non ho allocato memoria nuova, gli ho detto di puntare a vertex.position.x
    float &y = vertex.position.y;

    x = windowWidth * (x / (2*maxPos) + 0.5);
    y = windowHeight * (0.5 - y / (2*maxPos));
};


