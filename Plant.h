
#ifndef PLANT_H
#define PLANT_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "tile.h"
using namespace sf;

class Plant : public tile {
 protected:
  int growTime;
  int seedingTime;  // how many days ago it was seeded
  int costPrice;
  int sellPrice;
  bool alive;
  int growthStage;  // associated with time after planting
  int yield;
  int harvestEquipment;
  Texture growthImage;

 public:
  Plant(int _x, int _y) : tile::tile(_x, _y) {
    x = _x;
    y = _y;
    int size = 50;
    isPlantable = false;  // cannot plant ontop of another plant tile
    square = new RectangleShape(Vector2f(size, size));
    growthImage.loadFromFile("textures/cheese.png");
    square->setTexture(&growthImage);
    square->setTextureRect(IntRect(0, 0, size, size));
    if (!growthImage.loadFromFile("textures/cheese.png")) {
      std::cout << "error loading texture" << std::endl;
    }
    square->setPosition(_x, _y);

    // necessary values
    growthStage = 0;
    alive = true;
    hydrationLevel = 0;
    seedingTime = 0;

    // arbitrary placeholder values (initialise everything to 0)
    growTime = 0;
    costPrice = 0;
    sellPrice = 0;
    yield = 0;
    harvestEquipment = 0;
  };

  Plant() : Plant(0, 0){};

  // Harvest yield will produce a different harvest yeild
  // for each sub category of plant. Plants by themselves do not have harvest
  // yeild.
  virtual int harvestYield() = 0;

  void newDayGrowth() {
    // Plant growth will change the plant values for each new day, returns
    // nothing.
    if (hydrationLevel == 0) {
      alive = false;
    }

    if (growthStage < growTime && alive == true) {
      growthStage++;
    }
    hydrationLevel--;
    seedingTime++;
    return;
  };

  // The setters
  void set_growTime(int growTime) {
    this->growTime = growTime;
    return;
  };
  void set_seedingTime(int seedingTime) {
    this->seedingTime = seedingTime;
    return;
  };
  void set_costPrice(int costPrice) {
    this->costPrice = costPrice;
    return;
  };
  void set_sellPrice(int sellPrice) {
    this->sellPrice = sellPrice;
    return;
  };
  void set_alive(bool alive) {
    this->alive = alive;
    return;
  };
  void set_growthStage(int growthStage) {
    this->growthStage = growthStage;
    return;
  };
  void set_yield(int yield) {
    this->yield = yield;
    return;
  };
  void set_harvestEquipment(int harvestEquipment) {
    this->harvestEquipment = harvestEquipment;
    return;
  };

  // The getters
  int get_growTime() { return growTime; };
  int get_seedingTime() { return seedingTime; };
  int get_costPrice() { return costPrice; };
  int get_sellPrice() { return sellPrice; };
  bool get_alive() { return alive; };
  int get_growthStage() { return growthStage; };
  int get_yield() { return yield; };
  int get_harvestEquipment() { return harvestEquipment; };

  ~Plant(){};
};

#endif