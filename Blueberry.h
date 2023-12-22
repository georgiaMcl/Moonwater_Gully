
#ifndef BLUEBERRY_H
#define BLUEBERRY_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BerryPlant.h"
#include "Plant.h"
#include "tile.h"

using namespace sf;

class Blueberry : public BerryPlant {
 public:
  Blueberry(int _x, int _y) : BerryPlant(_x, _y) {
    harvestEquipment = 1;  // need level 1 harvest equipment to harvest
    sellPrice = 120;       // sells for 120 shells
    imageDescription = "textures/blueberrySeeds.png";
    className = "Blueberry";
    growthImage.loadFromFile("textures/blueberrySeeds.png");
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!growthImage.loadFromFile("textures/blueberrySeeds.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);
  };

  Blueberry() : BerryPlant(0, 0){};

  void grow() {
    // changes growth image if growth criteria has been met
    if (hydrationLevel == 0 && alive && growthStage <= growTime) {
      int size = 50;
      square = new RectangleShape(Vector2f(size, size));

      // sets new growth image for each stage of growth
      switch (growthStage) {
        case 1:
          imageDescription = "textures/blueberrySeedling.png";
          break;

        case 2:
          imageDescription = "textures/blueberrybushGrown.png";
          break;

        default:  // testing to see if it breaks by planting cheese
          imageDescription = "textures/cheese.png";
          // shouldn't get to default case, throws error and terminates program
          throw "Blueberry growth stage unregistered";
          break;
      }
      // loads new growth image
      growthImage.loadFromFile(imageDescription);
      square->setTexture(&growthImage);
      square->setTextureRect(IntRect(0, 0, size, size));
      if (!growthImage.loadFromFile(imageDescription)) {
        std::cout << "error loading texture" << std::endl;
      }
      square->setPosition(x, y);
    };
    return;
  };

  ~Blueberry(){};
};

#endif
