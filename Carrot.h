
#ifndef CARROT_H
#define CARROT_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Plant.h"
#include "RootPlant.h"
#include "tile.h"

using namespace sf;

class Carrot : public RootPlant {
 public:
  Carrot(int _x, int _y) : RootPlant(_x, _y) {
    harvestEquipment = 2;  // need level 2 harvest equipment to harvest
    sellPrice = 80;        // sells for 80 bells
    imageDescription = "textures/carrotSeeds.png";
    className = "Carrot";
    growthImage.loadFromFile("textures/carrotSeeds.png");
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!growthImage.loadFromFile("textures/carrotSeeds.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);
  };

  Carrot() : RootPlant(0, 0){};

  void grow() {
    // Changes growth image if growth criteria has been met
    // std::cout << "hydration level: " << hydrationLevel << " alive: " << alive
    // << std::endl;

    if (hydrationLevel == 0 && alive && growthStage <= growTime) {
      int size = 50;
      square = new RectangleShape(Vector2f(size, size));
      // sets the growth image depending on its growth stage
      switch (growthStage) {
        case 1:
          imageDescription = "textures/carrotGrown.png";
          break;
        default:  // testing to see if it breaks by planting cheese
          imageDescription = "textures/cheese.png";
          // shouldn't get to default case, throws error and terminates program
          throw "Carrot growth stage unregistered";
          break;
      }
      // loads the growth image
      growthImage.loadFromFile(imageDescription);
      square->setTexture(&growthImage);
      square->setTextureRect(IntRect(0, 0, size, size));
      if (!growthImage.loadFromFile(imageDescription)) {
        std::cout << "error loading texture" << std::endl;
      }
      square->setPosition(x, y);
    }
    return;
  };

  ~Carrot(){};
};

#endif
