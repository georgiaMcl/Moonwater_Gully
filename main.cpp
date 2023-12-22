#include <SFML/Graphics.hpp>

// Compile Command:
// g++ main.cpp -o main -I include -L lib -l sfml-system -l sfml-window -l
// sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib

// using namespace sf (means it doesn't need sf:: before everything)
using namespace sf;
int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(10.f);
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(Vector2f(5, 5));
  shape.setPosition(Vector2f(100, 100));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      Vector2f pose = shape.getPosition();
      pose.x = pose.x - 1;
      shape.setPosition(pose);

    } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
      Vector2f pose = shape.getPosition();
      pose.x = pose.x + 1;
      shape.setPosition(pose);
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}