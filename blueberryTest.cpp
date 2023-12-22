#include <SFML/Graphics.hpp>
#include <iostream>

#include "BerryPlant.h"
#include "Blueberry.h"
#include "Plant.h"
#include "tile.h"
using namespace sf;

// g++ RootPlant.cpp -o rootplant -I include -L lib -l sfml-system -l
// sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath
// -std=c++11 ./lib
class TileDriver {
 private:
  RenderWindow* win;
  //   tile** background = new tile*[400];  // array of tile pointers
  std::vector<tile*> background;
  Blueberry b = Blueberry(100, 100);

 public:
  TileDriver(int size, std::string title) {
    win = new sf::RenderWindow(sf::VideoMode(size, size), title);
    b.set_hydrationLevel(1);

    // uncomment to see each growth stage
    b.grow();
    b.set_hydrationLevel(1);
    b.grow();
  };

  void makeBackground() {
    // Creates the tile game background
    for (int r = 0; r < 600; r += 50) {
      for (int c = 0; c < 600; c += 50) {
        tile* newTile = new tile(r, c);  // Pass coordinates to tile constructor
        background.push_back(newTile);
      }
    }
    return;
  };

  void run() {
    // Running the game
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
      b.draw(win);

      win->display();
    }
    return;
  };
  ~TileDriver(){};

  // getter

  std::vector<tile*> get_background() { return background; }
};

int main() {
  Blueberry b1(50, 50);

  std::cout << "The blueberry plant has a cost price of 70:"
            << b1.get_costPrice()
            << ", a sell price of 120:" << b1.get_sellPrice()
            << ", a growTime of 2:" << b1.get_growTime()
            << ", requires havestEquipment level 1:"
            << b1.get_harvestEquipment()
            << ", and has image description textures/blueberrySeeds.png:"
            << b1.get_imageDescription() << std::endl;

  b1.harvestYield();

  std::cout << "The blueberry plant has harvest yield of (number 3-6):"
            << b1.get_yield() << std::endl;

  std::cout << "The blueberry plant has hydration level 0:"
            << b1.get_hydrationLevel()
            << ", and is alive (should be 1):" << b1.get_alive() << std::endl;

  b1.set_hydrationLevel(1);
  std::cout << "The blueberry plant has hydration level 1:"
            << b1.get_hydrationLevel()
            << ", and is alive (should be 1):" << b1.get_alive() << std::endl;

  b1.newDayGrowth();
  b1.grow();

  std::cout << "the blueberry is in growthStage 1:" << b1.get_growthStage()
            << ", has hydration level 0: " << b1.get_hydrationLevel()
            << ", and image description blueberrySeedling.png:"
            << b1.get_imageDescription() << std::endl;

  b1.newDayGrowth();
  std::cout << "The blueberry plant has hydration level -1:"
            << b1.get_hydrationLevel()
            << ", The blueberry plant was seeded 2 days ago:"
            << b1.get_seedingTime()
            << ", plant is alive (should be 0):" << b1.get_alive() << std::endl;

  b1.set_alive(true);
  b1.set_hydrationLevel(1);
  b1.newDayGrowth();
  b1.grow();
  std::cout << "the blueberry plant is in growthStage 2:"
            << b1.get_growthStage()
            << ", has hydration level 0: " << b1.get_hydrationLevel()
            << ", and image description blueberrybushGrown.png:"
            << b1.get_imageDescription() << std::endl;

  Blueberry b2(50, 50);
  // test to see that it doesn't exceed growth of 2
  b2.set_hydrationLevel(1);
  b2.newDayGrowth();
  b2.set_hydrationLevel(1);
  b2.newDayGrowth();
  b2.set_hydrationLevel(1);
  b2.newDayGrowth();
  b2.set_hydrationLevel(1);
  b2.newDayGrowth();
  std::cout << "the blueberry is in growthStage 2:" << b2.get_growthStage()
            << std::endl;

  // Ensuring that it catches error thrown in carrot
  Blueberry b3(150, 150);

  b3.set_hydrationLevel(1);
  b3.newDayGrowth();

  try {
    b3.grow();
    b3.set_hydrationLevel(1);
    b3.newDayGrowth();
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  TileDriver driver(600, "TEST");
  driver.makeBackground();
  driver.run();
  return 0;
}
