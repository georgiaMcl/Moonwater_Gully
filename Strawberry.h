
#ifndef STRAWBERRY_H
#define STRAWBERRY_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BerryPlant.h"
#include "Plant.h"
#include "tile.h"

using namespace sf;

class Strawberry : public BerryPlant {
 public:
  Strawberry(int _x, int _y) : BerryPlant(_x, _y) {
    harvestEquipment = 1;  // requires harvest equipment level 1
    sellPrice = 200;       // sells for 200 shells
    imageDescription = "textures/strawberrySeeds.png";
    className = "Strawberry";
    growthImage.loadFromFile(
        "textures/strawberrySeeds.png");  // change to different seed texture
                                          // for each plant type
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!growthImage.loadFromFile("textures/strawberrySeeds.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);
  };

  Strawberry() : BerryPlant(0, 0){};

  void grow() {
    // changes growth image if growth criteria has been met
    if (hydrationLevel == 0 && alive && growthStage <= growTime) {
      int size = 50;
      square = new RectangleShape(Vector2f(size, size));
      // sets new image for each growth stage
      switch (growthStage) {
        case 1:
          imageDescription = "textures/strawberrySeedling.png";
          break;

        case 2:
          imageDescription =
              "textures/strawberrybushGrown.png";  // image from
                                                   // https://www.istockphoto.com/vector/wild-strawberries-on-a-bush-growing-in-a-bed-pixel-art-icon-old-school-8-bit-gm926753458-254277720
          break;

        default:  // to know when it breaks it plants cheese
          imageDescription = "textures/cheese.png";
          // shouldn't get to default case, throws error and terminates program
          throw "Strawberry growth stage unregistered";
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
  ~Strawberry(){};
};

#endif
