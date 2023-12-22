#include <SFML/Graphics.hpp>
#include <iostream>

#include "Plant.h"
#include "Potato.h"
#include "RootPlant.h"
#include "tile.h"
using namespace sf;

class TileDriver {
 private:
  RenderWindow* win;
  std::vector<tile*> background;
  Potato p = Potato(350, 350);

 public:
  TileDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    p.set_hydrationLevel(1);

    // uncomment to see potato grow
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
  Potato p1(50, 50);

  std::cout << "The potato plant has a cost price of 50:" << p1.get_costPrice()
            << ", a sell price of 100:" << p1.get_sellPrice()
            << ", a growTime of 1:" << p1.get_growTime()
            << ", requires havestEquipment level 1:"
            << p1.get_harvestEquipment()
            << ", and has image description textures/potatoSeeds.png:"
            << p1.get_imageDescription() << std::endl;

  p1.harvestYield();

  std::cout << "The potato plant has harvest yield of (number 1-3):"
            << p1.get_yield() << std::endl;

  std::cout << "The potato plant has hydration level 0:"
            << p1.get_hydrationLevel()
            << ", and is alive (should be 1):" << p1.get_alive() << std::endl;

  p1.set_hydrationLevel(1);
  std::cout << "The potato plant has hydration level 1:"
            << p1.get_hydrationLevel()
            << ", and is alive (should be 1):" << p1.get_alive() << std::endl;

  p1.newDayGrowth();
  try {
    p1.grow();
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  std::cout << "the potato is in growthStage 1:" << p1.get_growthStage()
            << ", has hydration level 0: " << p1.get_hydrationLevel()
            << ", and image description textures/potatoGrown.png:"
            << p1.get_imageDescription() << std::endl;

  p1.newDayGrowth();
  try {
    p1.grow();
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }
  std::cout << "The potato plant has hydration level -1:"
            << p1.get_hydrationLevel()
            << ", The root plant was seeded 2 days ago:" << p1.get_seedingTime()
            << ", plant is alive (should be 0):" << p1.get_alive() << std::endl;

  p1.grow();
  try {
    p1.grow();
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }
  p1.newDayGrowth();
  std::cout << "the potato plant is in growthStage 1:" << p1.get_growthStage()
            << ", has hydration level -2: " << p1.get_hydrationLevel()
            << ", and image description textures/potatGrown.png:"
            << p1.get_imageDescription() << std::endl;

  Potato p2(50, 50);
  // test to see that it doesn't exceed growth of 1
  p2.set_hydrationLevel(1);
  p2.newDayGrowth();
  p2.set_hydrationLevel(1);
  p2.newDayGrowth();
  p2.set_hydrationLevel(1);
  p2.newDayGrowth();
  p2.set_hydrationLevel(1);
  p2.newDayGrowth();
  std::cout << "the rootplant is in growthStage 1:" << p2.get_growthStage()
            << std::endl;

  // Ensuring that it catches error thrown in carrot
  Potato p3(150, 150);

  p3.set_hydrationLevel(1);
  p3.newDayGrowth();

  try {
    p3.grow();
    p3.set_hydrationLevel(1);
    p3.newDayGrowth();
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  TileDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}
