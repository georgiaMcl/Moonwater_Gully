#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
#include <unistd.h>

#include <chrono>
#include <cmath>
#include <thread>
#include <typeinfo>
#include <unordered_map>

#include "Blueberry.h"
#include "Carrot.h"
#include "Inventory.h"
#include "Plant.h"
#include "Player.h"
#include "Potato.h"
#include "Strawberry.h"

// #include "PlayerInteraction.h"

class Player {
 private:
  std::string name;
  RectangleShape* body;
  int x, y;
  float speed;
  int shells;
  Texture playerTexture;
  std::string textureName;
  // these two variables are for player walking animation
  int countSteps;
  bool imgAppears;
  // For warnings
  RectangleShape warningMessage;
  Texture warningTexture;

  std::unordered_map<std::string, int> plantLocationMap{
      {"Carrot", 9}, {"Potato", 7}, {"Strawberry", 5}, {"Blueberry", 3}};

  // Doing the map
  Carrot* carrot = new Carrot(650, 650);
  Potato* potato = new Potato(650, 650);
  Strawberry* strawberry = new Strawberry(650, 650);
  Blueberry* blueberry = new Blueberry(650, 650);
  std::unordered_map<std::string, Plant*> plantMap{{"Carrot", carrot},
                                                   {"Potato", potato},
                                                   {"Strawberry", strawberry},
                                                   {"Blueberry", blueberry}};

 public:
  Player(int r, int _x, int _y) {
    body = new RectangleShape();
    x = _x;
    y = _y;
    shells = 500;
    speed = 2;
    countSteps = 0;
    imgAppears = 0;

    textureName = "textures/facingBack1.png";
    playerTexture.loadFromFile(textureName);
    if (!playerTexture.loadFromFile(textureName)) {
      std::cout << "Could not load the default texture" << std::endl;
      return;
    }
    body->setSize(Vector2f(40, 60));
    body->setTexture(&playerTexture);
    body->setTextureRect(IntRect(0, 0, 40, 60));
    // body->setFillColor(Color::Blue);
    body->setOrigin(r / 2, r / 2);
    body->setPosition(x, y);

    // text box font

    // warning ~ image is 90x48
    warningMessage.setSize(Vector2f(90,48));
    warningTexture.loadFromFile("textures/cantHarvest.png");
    warningMessage.setTexture(&warningTexture);
    warningMessage.setTextureRect(IntRect(0, 0, 90, 48));
    warningMessage.setPosition(700,700);
    

  }

  void draw(RenderWindow* win) {
    // Draws warning message in window, takes in a RenderWindow pointer, returns nothing
    win->draw(*body);
    win->draw(warningMessage);
    return;
  }


  // Seeding plant

  void seedPlant(int seedType, std::vector<tile*>* backgroundTiles) {
    // Seeds a plant by changing the tile the player is on to a seed type tile
    // (carrot, potato, blueberry, strawberry) Takes in an int representing
    // seedType and a pointer to a vector of tile pointers

    int playerX = (floor(body->getPosition().x / 50));
    int playerY = (floor(body->getPosition().y / 50));
    if ((*backgroundTiles)[playerX * 12 + playerY]->get_isPlantable() == true) {
      switch (seedType) {
        case 2:  // type 2 is blueberry seeds in inventory position 2
        {
          // create a new bluebbery tile (in the heap) with cooridnates of
          // player position and set blueberry as a pointer to the blueberry
          // tile
          Blueberry* blueberry = new Blueberry(playerX * 50, playerY * 50);
          // remove old tile from vector and replace with new carrot tile
          delete (*backgroundTiles)[playerX * 12 + playerY];
          // sets the current tile player is on to be a carrot tile
          (*backgroundTiles)[playerX * 12 + playerY] = blueberry;
          break;
        }

        case 4:  // type 4 is strawberry seeds in inventory position 4
        {
          // create a new strawberry tile (in the heap) with cooridnates of
          // player position and set strawberry as a pointer to the
          // strawberry tile
          Strawberry* strawberry = new Strawberry(playerX * 50, playerY * 50);
          // remove old tile from vector and replace with new carrot tile
          delete (*backgroundTiles)[playerX * 12 + playerY];
          // sets the current tile player is on to be a carrot tile
          (*backgroundTiles)[playerX * 12 + playerY] = strawberry;
          break;
        }

        case 6:  // type 6 is potato seeds in inventory position 6
        {
          // create a new potato tile (in the heap) with cooridnates of
          // player position and set potato as a pointer to the potato tile
          Potato* potato = new Potato(playerX * 50, playerY * 50);
          // remove old tile from vector and replace with new carrot tile
          delete (*backgroundTiles)[playerX * 12 + playerY];
          // sets the current tile player is on to be a carrot tile
          (*backgroundTiles)[playerX * 12 + playerY] = potato;
          break;
        }

        case 8:  // type 8 is carrot seeds in inventory position 8
        {
          // create a new carrot tile (in the heap) with cooridnates of
          // player position and set carrot as a pointer to the carrot tile
          Carrot* carrot = new Carrot(playerX * 50, playerY * 50);
          // remove old tile from vector and replace with new carrot tile
          delete (*backgroundTiles)[playerX * 12 + playerY];
          // sets the current tile player is on to be a carrot tile
          (*backgroundTiles)[playerX * 12 + playerY] = carrot;
          break;
        }

        default:
          std::cout << "error: could not plant as type was invalid"
                    << std::endl;
      };
    }
    return;
  }

  // Water plant

  void waterPlant(std::vector<tile*>* backgroundTiles) {
    // Waters the tile by increasing the hydration level, takes in a pointer to
    // a vector of tile pointers

    // changes the x and y coordinates of the player to valid tile positions
    int playerX = (floor(body->getPosition().x / 50));
    int playerY = (floor(body->getPosition().y / 50));

    (*backgroundTiles)[playerX * 12 + playerY]->set_hydrationLevel(1);

    // animating plant watered

    if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() == 0 &&
        (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
            "Carrot") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/carrotSeedsWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   0 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Potato") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/potatoSeedsWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   0 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Strawberry") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/strawberrySeedsWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   0 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Blueberry") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/blueberrySeedsWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   1 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Carrot") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/carrotWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   1 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Potato") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/potatoWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   1 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Strawberry") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/strawberrySeedlingWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   1 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Blueberry") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/blueberrySeedlingWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   2 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Strawberry") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/strawberryWatered.png");
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() ==
                   2 &&
               (*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Blueberry") {
      (*backgroundTiles)[playerX * 12 + playerY]->set_texture(
          "textures/blueberryWatered.png");
    }

    // Animating water plant

    std::string textureHold;
    textureHold = textureName;

    if (textureName == "textures/facingRight1.png" ||
        textureName == "textures/facingRight2.png" ||
        textureName == "textures/facingRight3.png") {
      textureName = "textures/waterRight.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading waterRight texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
    } else if (textureName == "textures/facingLeft1.png" ||
               textureName == "textures/facingLeft2.png" ||
               textureName == "textures/facingLeft3.png") {
      textureName = "textures/waterLeft.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading waterLeft texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
    } else if (textureName == "textures/facingForward1.png" ||
               textureName == "textures/facingForward2.png" ||
               textureName == "textures/facingForward3.png") {
      textureName = "textures/waterForward.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading waterForward texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
    } else if (textureName == "textures/facingBack1.png" ||
               textureName == "textures/facingBack2.png" ||
               textureName == "textures/facingBack3.png") {
      textureName = "textures/waterBack.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading waterBack texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
    }

    return;
  };

  void harvestPlant(std::vector<tile*>* backgroundTiles, Inventory* inventory) {
    // Takes the fully grown plant tile and changes it back to grass tile, and increases the number of plants in the inventory
    // Takes in a pointer to the vector of tile pointers and a pointer to the inventory

    // Takes the fully grown plant tile and changes it back to grass tile, and
    // increases the number of plants in the inventory Takes in a pointer to the
    // vector of tile pointers and a pointer to the inventory

    // Use a map once you have the type of function

    int playerX = (floor(body->getPosition().x / 50));
    int playerY = (floor(body->getPosition().y / 50));

    // Getting yield and inventory position
    int plantYield;
    int plantPos;

    // Setting a constant for easier readability. "currentPlant" just contains
    // an object of the same class as the plant the player is standing on.

    Plant* currentPlant =
        plantMap[(*backgroundTiles)[playerX * 12 + playerY]->get_className()];

    // Making sure all conditions are met
    if ((*backgroundTiles)[playerX * 12 + playerY]->get_className() == "tile") {
      warningMessage.setPosition(body->getPosition().x - 75,body->getPosition().y - 45);  
      std::cout << "Land cannot be harvested" << std::endl;
      // warningMessage.setPosition(300,20);
      return;
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_growthStage() !=
               currentPlant->get_growTime()) {
      warningMessage.setPosition(body->getPosition().x - 75,body->getPosition().y - 45);
      std::cout << "Please wait until plant is fully grown" << std::endl;
      return;
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Carrot" &&
               (inventory->get_inventoryIndex() != 1 ||
                inventory->get_gloveCount() == 0)) {
      warningMessage.setPosition(body->getPosition().x - 75,body->getPosition().y - 45);
      std::cout << "Must hold gloves to harvest this plant" << std::endl;
      return;
    } else if ((*backgroundTiles)[playerX * 12 + playerY]->get_className() ==
                   "Potato" &&
               (inventory->get_inventoryIndex() != 0 ||
                inventory->get_shovelCount() == 0)) {
      warningMessage.setPosition(body->getPosition().x - 75,body->getPosition().y - 45);
      std::cout << "Must hold a shovel to harvest this plant" << std::endl;
      return;
    }

    // Getting yield and inventory position

    plantYield =
        plantMap[(*backgroundTiles)[playerX * 12 + playerY]->get_className()]
            ->harvestYield();
    plantPos = plantLocationMap[(*backgroundTiles)[playerX * 12 + playerY]
                                    ->get_className()];

    // Adding plants to the Inventory

    std::cout << plantYield << std::endl;

    inventory->set_fromPos(plantPos,
                           inventory->get_fromPos(plantPos) + plantYield);

    // resetting position as a tile

    delete (*backgroundTiles)[playerX * 12 + playerY];

    (*backgroundTiles)[playerX * 12 + playerY] =
        new tile(playerX * 50, playerY * 50);
    return;
  }

  // movement of the player
  void moveRight() {
    countSteps++;
    // Moving player
    if (body->getPosition().x < 590) {
      body->move(speed, 0);
    }
    // checking if texture has already been loaded

    if (textureName == "textures/facingRight1.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingRight2.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingRight3.png") {
      imgAppears = 1;
    } else {
      imgAppears = 0;
    }

    if (!imgAppears) {
      warningMessage.setPosition(700, 700);
      textureName = "textures/facingRight1.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;

    } else if (countSteps == 15) {  // checking if image should be changed

      textureName = "textures/facingRight2.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);

    } else if (countSteps == 30) {
      textureName = "textures/facingRight3.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;
    }
    return;
  }
  void moveLeft() {
    countSteps++;
    if (body->getPosition().x > 0) {
      body->move(-speed, 0);
    }
    // checking if texture has already been loaded

    if (textureName == "textures/facingLeft1.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingLeft2.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingLeft3.png") {
      imgAppears = 1;
    } else {
      imgAppears = 0;
    }

    if (!imgAppears) {
      warningMessage.setPosition(700, 700);
      textureName = "textures/facingLeft1.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;

    } else if (countSteps == 15) {  // checking if image should be changed

      textureName = "textures/facingLeft2.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);

    } else if (countSteps == 30) {
      textureName = "textures/facingLeft3.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;
    }
    return;
  }
  void moveUp() {
    countSteps++;

    if (body->getPosition().y > 0) {
      body->move(0, -speed);
    }

    if (textureName == "textures/facingForward1.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingForward2.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingForward3.png") {
      imgAppears = 1;
    } else {
      imgAppears = 0;
    }

    if (!imgAppears) {
      warningMessage.setPosition(700, 700);
      textureName = "textures/facingForward1.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;

    } else if (countSteps == 15) {  // checking if image should be changed

      textureName = "textures/facingForward2.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);

    } else if (countSteps == 30) {
      textureName = "textures/facingForward3.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;
    }
    return;
  }
  void moveDown() {
    countSteps++;

    if (body->getPosition().y < 590) {
      body->move(0, speed);
    }

    if (textureName == "textures/facingBack1.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingBack2.png") {
      imgAppears = 1;
    } else if (textureName == "textures/facingBack1.png") {
      imgAppears = 1;
    } else {
      imgAppears = 0;
    }

    if (!imgAppears) {
      warningMessage.setPosition(700, 700);
      textureName = "textures/facingBack1.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;

    } else if (countSteps == 15) {  // checking if image should be changed

      textureName = "textures/facingBack2.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);

    } else if (countSteps == 30) {
      textureName = "textures/facingBack1.png";
      playerTexture.loadFromFile(textureName);
      if (!playerTexture.loadFromFile(textureName)) {
        std::cout << "Error loading texture" << std::endl;
        return;
      }
      body->setTexture(&playerTexture);
      countSteps = 0;
    }
    return;
  }

  // getters and setters
  int get_x() { return body->getPosition().x; }
  int get_y() { return body->getPosition().y; }

  void add80shells() { shells += 80; }
  void add100shells() { shells += 100; }
  void add120shells() { shells += 120; }
  void add200shells() { shells += 200; }

  void subtract50shells() { shells -= 50; }
  void subtract70shells() { shells -= 70; }
  void subtract400shells() { shells -= 400; }
  void subtract150shells() { shells -= 150; }

  int get_shells() { return shells; }
  void set_shells(int shellNo) { shells = shellNo; }
};

#endif