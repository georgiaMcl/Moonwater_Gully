#ifndef POTATO_H
#define POTATO_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Plant.h"
#include "RootPlant.h"
#include "tile.h"

using namespace sf;

class Potato : public RootPlant {
 public:
  Potato(int _x, int _y) : RootPlant(_x, _y) {
    harvestEquipment = 3;  // need harvest equipment level 3 to harvest
    sellPrice = 100;       // sells for 100 shells
    imageDescription = "textures/potatoSeeds.png";
    className = "Potato";
    growthImage.loadFromFile(
        "textures/potatoSeeds.png");  // this image can change later to correct
                                      // seed colour
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!growthImage.loadFromFile("textures/potatoSeeds.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);
  };

  Potato() : RootPlant(0, 0){};

  void grow() {
    // Changes growth image if growth criteria has been met

    if (hydrationLevel == 0 && alive && growthStage <= growTime) {
      int size = 50;
      square = new RectangleShape(Vector2f(size, size));
      // sets image to new growth image
      switch (growthStage) {
        case 1:
          imageDescription = "textures/potatoGrown.png";
          break;
        default:  // testing to see if it breaks by planting cheese
          imageDescription = "textures/cheese.png";
          // shouldn't get to default case, throws error and terminates program
          throw "Potato growth stage unregistered";
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

  ~Potato(){};
};

#endif
