#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

  // Caricamento dell'immagine da file
  sf::Image image;
  sf::Texture texture;
  sf::Color color(0,0,0,255);
  color.r=150;
  color.g=200;
  color.b=255;
  
  
  sf::RectangleShape rectangle(sf::Vector2f(800.f, 600.f));
  rectangle.setFillColor(color);
  if (!image.loadFromFile("gabbianella.gif")) {
    // Gestisci eventuali errori di caricamento dell'immagine
    return EXIT_FAILURE;
  }
  texture.loadFromImage(image);
  // Creazione dello sprite per visualizzare l'immagine
  sf::Sprite sprite(texture);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    window.draw(rectangle);
    window.draw(sprite);  // Disegna lo sprite sulla finestra
    window.display();
  }

  return 0;
}
