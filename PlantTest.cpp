#include <SFML/Graphics.hpp>
#include <iostream>

#include "Plant.h"
#include "tile.h"
using namespace sf;

class TileDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Plant p = Plant(50, 50);

 public:
  TileDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    p.set_costPrice(20);
    p.set_sellPrice(40);
    p.set_growTime(3);
    p.set_harvestEquipment(2);
    p.set_hydrationLevel(1);

    // p.grow();
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
      p.draw(win);

      win->display();
    }
    return;
  };

  // getter

  std::vector<tile*> get_background() { return background; }

  ~TileDriver(){};
};

int main() {
  Plant p1 = Plant(50, 50);

  p1.set_costPrice(20);
  p1.set_sellPrice(40);
  p1.set_growTime(3);
  p1.set_harvestEquipment(2);
  std::cout << "The plant has a cost price of 20:" << p1.get_costPrice()
            << ", a sell price of 40:" << p1.get_sellPrice()
            << ", a growTime of 3:" << p1.get_growTime()
            << ", and requires havestEquipment level 2:"
            << p1.get_harvestEquipment() << std::endl;

  // p1.killPlant();

  std::cout << "The plant has hydration level 0:" << p1.get_hydrationLevel()
            << ", and is alive (should be 1):" << p1.get_alive() << std::endl;

  p1.set_hydrationLevel(1);
  std::cout << "The plant has hydration level 1:" << p1.get_hydrationLevel()
            << ", and is alive (should be 1):" << p1.get_alive() << std::endl;

  p1.newDayGrowth();
  p1.grow();

  std::cout << "the plant is in growthStage 1:" << p1.get_growthStage()
            << ", has hydration level 0: " << p1.get_hydrationLevel()
            << ", and image description grass_texture_light.png:"
            << p1.get_imageDescription() << std::endl;

  p1.newDayGrowth();
  // p1.killPlant();
  std::cout << "The plant has hydration level -1:" << p1.get_hydrationLevel()
            << ", The plant was seeded 2 days ago:" << p1.get_seedingTime()
            << ", plant is alive (should be 0):" << p1.get_alive() << std::endl;

  p1.grow();
  std::cout << "the plant is in growthStage 1:" << p1.get_growthStage()
            << ", has hydration level -1: " << p1.get_hydrationLevel()
            << ", and image description grass_texture_light.png:"
            << p1.get_imageDescription() << std::endl;

  TileDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}
