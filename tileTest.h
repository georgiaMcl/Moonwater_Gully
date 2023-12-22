#ifndef TILE_TEST
#define TILE_TEST
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class tile {
 protected:
  int x, y;
  int size;
  RectangleShape* square;
  Texture grass;

 public:
  tile(int _x, int _y) {
    x = _x;
    y = _y;
    size = 50;
    square = new RectangleShape(Vector2f(size, size));
    grass.loadFromFile("textures/grass_texture_light.png");
    square->setTexture(&grass);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!grass.loadFromFile("textures/grass_texture_light.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(x, y);
  };

  tile() : tile(0, 0) { size = 50; };

  void draw(RenderWindow* win) {
    // Draws a tile in the window when given a RenderWindow pointer
    win->draw(*square);
    return;
  };

  // Setters
  void set_x(int _x) {
    x = _x;
    return;
  };
  void set_y(int _y) {
    y = _y;
    return;
  };

  void set_texture(std::string TextureName) {
    Texture texture;
    texture.loadFromFile(TextureName);
    square->setTexture(&texture);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!texture.loadFromFile(TextureName)) {
      std::cout << "error loading texture" << std::endl;
    };
    return;
  }

  // Getters

  int get_x() { return x; }

  int get_y() { return y; }

  ~tile(){};
};

#endif
