#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
#include "tile.h"

class TileDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;

 public:
  TileDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
  };

  void makeBackground() {
    // Creates game background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to
                                         // tile constructor
        background.push_back(newTile);
      }
    }
    background[10]->set_texture("textures/grass_texture.png");
    return;
  };

  void run() {
    // Runs game
    while (win->isOpen()) {
      Event e;
      while (win->pollEvent(e)) {
        if (e.type == Event::Closed) {
          win->close();
        }
      }
      win->clear();

      // drawing the tiles
      for (auto tilePtr : background) {
        tilePtr->draw(win);
      }

      win->display();
    }
    return;
  };

  // getter
  std::vector<tile*> get_background() { return background; }

  ~TileDriver(){};
};

int main() {
  TileDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}