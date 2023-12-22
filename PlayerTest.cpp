#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
#include "Plant.h"
#include "Player.h"
#include "tile.h"

class PlayerDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  // creation of player class
  Player* player;
  Plant p1 = Plant(50, 50);

 public:
  PlayerDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    player = new Player(10, 50, 50);
    // player->addPlant(plant);
    p1.set_costPrice(20);
    p1.set_sellPrice(40);
    p1.set_growTime(3);
    p1.set_harvestEquipment(2);
  };

  void makeBackground() {
    // Creates game background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to tile constructor
        background.push_back(newTile);
      }
    }
    return;
  };

  void run() {
    // Runs the game
    while (win->isOpen()) {
      Event e;
      while (win->pollEvent(e)) {
        if (e.type == Event::Closed) {
          win->close();
        }
      }

      if (Keyboard::isKeyPressed(Keyboard::A)) {
        player->moveLeft();
      } else if (Keyboard::isKeyPressed(Keyboard::D)) {
        player->moveRight();
      } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        player->moveUp();
      } else if (Keyboard::isKeyPressed(Keyboard::S)) {
        player->moveDown();
      }

      // drawing the tiles
      for (auto tilePtr : background) {
        tilePtr->draw(win);
      };
      player->draw(win);
      p1.draw(win);

      win->display();
    }
    return;
  };

  std::vector<tile*> get_background() { return background; };

  ~PlayerDriver(){};
};

int main() {
  PlayerDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}
