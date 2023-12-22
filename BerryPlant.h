#ifndef BERRYPLANT_H
#define BERRYPLANT_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BerryPlant.h"
#include "Plant.h"
#include "tile.h"

using namespace sf;

class BerryPlant : public Plant {
 public:
  BerryPlant(int _x, int _y) : Plant(_x, _y) {
    // Constructor for BerryPlant
    growTime = 2;    // takes 2 days to grow
    costPrice = 70;  // cost 70 shells to buy
    imageDescription = "textures/carrotSeeds.png";
    growthImage.loadFromFile(
        "textures/carrotSeeds.png");  // starting seed image
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    // Error checking that texture loaded correctly
    if (!growthImage.loadFromFile("textures/carrotSeeds.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);
  };

  BerryPlant()
      : BerryPlant(0, 0){
            // Default onstructor for BerryPlant
        };

  int harvestYield() {
    // Creates and returns a randomised yield value between 3 and 6 (inclusive)
    // for all BerryPlants
    srand(time(NULL));
    yield = (rand() % 3) + 3;
    return yield;
  }
  ~BerryPlant(){};
};
#endif
