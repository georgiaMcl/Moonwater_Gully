#include <SFML/Graphics.hpp>
#include <iostream>

#include "Plant.h"
#include "RootPlant.h"
#include "tile.h"
using namespace sf;

class TileDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  RootPlant rp = RootPlant(250, 250);

 public:
  TileDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    rp.set_sellPrice(40);
    rp.set_harvestEquipment(2);
    rp.set_hydrationLevel(1);

    // rp.grow();
  };

  void makeBackground() {
    // Create game background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to tile constructor
        background.push_back(newTile);
      }
    }
    return;
  };

  void run() {
    // Run game
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
      rp.draw(win);

      win->display();
    }
    return;
  };

  // getter

  std::vector<tile*> get_background() { return background; }

  ~TileDriver(){};
};

int main() {
  RootPlant rp1(50, 50);

  std::cout << "The root plant has a cost price of 50:" << rp1.get_costPrice()
            << ", a sell price of 0:" << rp1.get_sellPrice()
            << ", a growTime of 1:" << rp1.get_growTime()
            << ", and requires havestEquipment level 0:"
            << rp1.get_harvestEquipment() << std::endl;

  rp1.harvestYield();

  std::cout << "The root plant has harvest yield of (number 1-3):"
            << rp1.get_yield() << std::endl;

  std::cout << "The root plant has hydration level 0:"
            << rp1.get_hydrationLevel()
            << ", and is alive (should be 1):" << rp1.get_alive() << std::endl;

  rp1.set_hydrationLevel(1);
  std::cout << "The root plant has hydration level 1:"
            << rp1.get_hydrationLevel()
            << ", and is alive (should be 1):" << rp1.get_alive() << std::endl;

  rp1.newDayGrowth();

  std::cout << "the rootplant is in growthStage 1:" << rp1.get_growthStage()
            << ", has hydration level 0: " << rp1.get_hydrationLevel()
            << ", and image description textures/carrotSeeds.png:"
            << rp1.get_imageDescription() << std::endl;

  rp1.newDayGrowth();
  std::cout << "The root plant has hydration level -1:"
            << rp1.get_hydrationLevel()
            << ", The root plant was seeded 2 days ago:"
            << rp1.get_seedingTime()
            << ", plant is alive (should be 0):" << rp1.get_alive()
            << std::endl;

  rp1.newDayGrowth();
  std::cout << "the root plant is in growthStage 1:" << rp1.get_growthStage()
            << ", has hydration level -2: " << rp1.get_hydrationLevel()
            << std::endl;

  RootPlant rp2(50, 50);
  // test to see that it doesn't exceed growth of 1
  rp2.set_hydrationLevel(1);
  rp2.newDayGrowth();
  rp2.set_hydrationLevel(1);
  rp2.newDayGrowth();
  rp2.set_hydrationLevel(1);
  rp2.newDayGrowth();
  rp2.set_hydrationLevel(1);
  rp2.newDayGrowth();
  std::cout << "the rootplant is in growthStage 1:" << rp2.get_growthStage()
            << std::endl;

  TileDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}
