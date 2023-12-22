#ifndef ROOTPLANT_H
#define ROOTPLANT_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Plant.h"
#include "tile.h"

using namespace sf;

class RootPlant : public Plant {
 public:
  RootPlant(int _x, int _y) : Plant(_x, _y) {
    growTime = 1;    // takes 1 day to grow
    costPrice = 50;  // costs 50 shells to buy seeds
    imageDescription = "textures/carrotSeeds.png";
    growthImage.loadFromFile(
        "textures/carrotSeeds.png");  // orignial seeding image
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!growthImage.loadFromFile("textures/carrotSeeds.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);
  };

  RootPlant() : RootPlant(0, 0){};

  int harvestYield() {
    // harvest yield will return a random yield value between 1-3 (inclusive)
    srand(time(NULL));
    yield = (rand() % 3) + 1;
    return yield;
  }

  ~RootPlant(){};
};

#endif
