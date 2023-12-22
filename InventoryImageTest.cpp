
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "BuyMenu.h"
#include "Inventory.h"
#include "InventoryItems.h"
#include "Menu.h"
#include "Player.h"
#include "SellMenu.h"
#include "tile.h"
using namespace sf;

class InventoryImageTest {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Inventory inventory = Inventory(55, 550);

 public:
  InventoryImageTest(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
  }
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
        if (e.type == Event::KeyPressed) {
          if (Keyboard::isKeyPressed(Keyboard::Space)) {
            inventory.scrollInventory();
          }
        }
      }
      win->clear();
      // drawing the tiles
      for (auto tilePtr : background) {
        tilePtr->draw(win);
      }
      inventory.drawInventory(win);
      inventory.drawCounter(win);
      win->display();
    }
    return;
  }

  ~InventoryImageTest(){};
};

int main() {
  InventoryImageTest driver(600, "please");
  driver.makeBackground();
  driver.run();
  return 0;
}